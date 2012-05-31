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
#include <tr1/unordered_map>

class Engine;

namespace pp {
    
    class View {
    private:
        int opacity;
        bool hidden;
        
        
        std::tr1::unordered_map<std::string, pp::View*> children;
        
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
            removeAllChildren();
            children.clear();
        }
        
        // Getters & setters
        int getOpacity() {return this->opacity;}
        void setOpacity(int opacity) {
            this->opacity = (opacity > 100) ? 100 : (opacity < 0) ? 0 : opacity;
        }
        
        void setVisible(bool visible) {visible ? this->hidden=false : this->hidden=true;}
        bool isVisible() {return !(this->hidden);}
        
        pp::View* getChild(std::string name) {return children[name];}
        void addChild(std::string name, pp::View* view) {this->children[name] = view;}
        void removeChild(std::string name) {
            std::tr1::unordered_map<std::string, pp::View*>::iterator it;
            if ((it = children.find(name)) != children.end()) {
                delete (*it).second;
                children.erase(it);
            }
        }
        void removeChildAt(int index) {
            std::tr1::unordered_map<std::string, pp::View*>::iterator it;
            it = children.begin();
            int i = 0;
            while (i < index) {
                it++;
                i++;
            }
            if (it != children.end()) {
                removeChild((*it).first);
            }
        }
        void removeAllChildren() {
            std::tr1::unordered_map<std::string, pp::View*>::iterator it;
            for (it=children.begin(); it != children.end(); it++) {
                delete (*it).second;
            }
            children.clear();
        }
        
        
        // draw this view and its children
        void doDraw(sf::RenderWindow *window) {
            if (isVisible()) {
                this->draw(window);
                
                std::tr1::unordered_map<std::string, pp::View*>::iterator it;
                for (it = children.begin(); it != children.end(); it++) {
                    (*it).second->doDraw(window);
                }
            }
        }
        
        // update this view and its children
        void doUpdate() {
            this->update();
            
            std::tr1::unordered_map<std::string, pp::View*>::iterator it;
            for (it = children.begin(); it != children.end(); it++) {
                (*it).second->doUpdate();
            }
        }
    };
    
}

#endif
