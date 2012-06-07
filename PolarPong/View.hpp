//
//  View.hpp
//  PolarPong
//
//  Created by Callum Chalk on 05/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PolarPong_Viewa_hpp
#define PolarPong_Viewa_hpp

#include <SFML/Graphics.hpp>
#include <map>

class Engine;

namespace pp {
    
    class View : public sf::Transformable, public sf::Drawable {
    private:
        int opacity;
        bool hidden;
        sf::Vector2f size;
        
        typedef std::map<std::string, pp::View*> ViewMap;
        
        View* parent;
        ViewMap children;
        
    protected:
        // for subclass instantiation
        View() : parent(NULL), opacity(100), hidden(false) {}
        
        // update this view
        virtual void update() = 0;
        
        sf::Mutex mutex;
        
    public:
        virtual ~View() {
            // delete child views
            mutex.lock();
            removeAllChildren();
            children.clear();
            mutex.unlock();
        }
        
        // Getters & setters
        int getOpacity() {return this->opacity;}
        void setOpacity(int opacity) {
            this->opacity = (opacity > 100) ? 100 : (opacity < 0) ? 0 : opacity;
        }
        
        void setVisible(bool visible) {visible ? this->hidden=false : this->hidden=true;}
        bool isVisible() {return !(this->hidden);}
        
        void setSize(float x, float y) {
            setSize(sf::Vector2f(x,y));
        }
        void setSize(sf::Vector2f size) {
            this->size = size;
        }
        sf::Vector2f getSize() {
            return this->size;
        }
        
        const sf::Vector2f getGlobalPosition() const {
            // return position in global coordinates
            sf::Transform transform = getTransform();
            View* parent = getParent();
            while (parent != NULL) {
                transform *= parent->getTransform();
                parent = parent->getParent();
            }
            
            return transform.transformPoint(getPosition());
        }
        
        View* getParent() const {
            return this->parent;
        }
        
    private:
        void setParent(View* parent) {
            this->parent = parent;
        }
        
    public:
        
        pp::View* getChild(std::string name) {
            View* view = NULL;
            mutex.lock();
            if (children.count(name) > 0) {
                view = children[name];
            }
            mutex.unlock();
            return view;
        }
        void addChild(std::string name, pp::View* view) {
            mutex.lock();
            this->children[name] = view;
            children[name]->setParent(this);
            mutex.unlock();
        }
        void removeChild(std::string name) {
            ViewMap::iterator it;
            mutex.lock();
            if ((it = children.find(name)) != children.end()) {
                delete (*it).second;
                children.erase(it);
            }
            mutex.unlock();
        }
        void removeChildAt(int index) {
            ViewMap::iterator it;
            mutex.lock();
            it = children.begin();
            int i = 0;
            while (i < index) {
                it++;
                i++;
            }
            if (it != children.end()) {
                removeChild((*it).first);
            }
            mutex.unlock();
        }
        void removeAllChildren() {
            ViewMap::iterator it;
            mutex.lock();
            for (it=children.begin(); it != children.end(); it++) {
                delete (*it).second;
            }
            children.clear();
            mutex.unlock();
        }
        
        
        // draw this view and its children
        void doDraw(sf::RenderTarget &target, sf::RenderStates states) {
            if (isVisible()) {
                mutex.lock();
                states.transform *= this->getTransform();
                
                target.draw(*this, states);
                
                ViewMap::iterator it;
                for (it = children.begin(); it != children.end(); it++) {
                    (*it).second->doDraw(target, states);
                }
                
                mutex.unlock();
            }
        }
        
        // update this view and its children
        void doUpdate() {
            mutex.lock();
            
            this->update();
            
            ViewMap::iterator it;
            for (it = children.begin(); it != children.end(); it++) {
                (*it).second->doUpdate();
            }
            
            mutex.unlock();
        }
    };
    
}

#endif
