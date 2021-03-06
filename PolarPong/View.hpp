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
    
    class View {
    private:
        int opacity;
        bool hidden;
        
        typedef std::map<std::string, pp::View*> ViewMap;
        
        sf::Mutex mutex;
        
        ViewMap children;
        
    protected:
        // for subclass instantiation
        View() : opacity(100), hidden(false) {}
        
        // draw this view
        virtual void draw(sf::RenderWindow *window) =0;
        
        // update this view
        virtual void update() = 0;
        
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
        
        pp::View* getChild(std::string name) {
            mutex.lock();
            View* view = children[name];
            mutex.unlock();
            return view;
        }
        void addChild(std::string name, pp::View* view) {
            mutex.lock();
            this->children[name] = view;
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
        void doDraw(sf::RenderWindow *window) {
            if (isVisible()) {
                mutex.lock();
                this->draw(window);
                
                ViewMap::iterator it;
                for (it = children.begin(); it != children.end(); it++) {
                    (*it).second->doDraw(window);
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
