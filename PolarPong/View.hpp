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

class View {
private:
    int opacity;
    bool hidden;
    
    
    std::tr1::unordered_map<std::string, View*> children;
    
protected:
    // for subclass instantiation
    View() : opacity(100), hidden(true) {}
    
    // this *must* be called by subclass on destruction
    void destruct() {
        // delete child views
        std::tr1::unordered_map<std::string, View*>::iterator it;
        for (it=children.begin(); it != children.end(); it++) {
            delete (*it).second;
        }
        children.clear();
    }
    
    // draw this view
    virtual void draw(sf::RenderWindow *window) =0;
    
public:
    virtual ~View() {destruct();}
    
    // Getters & setters
    int getOpacity() {return this->opacity;}
    void setOpacity(int opacity) {
        this->opacity = (opacity > 100) ? 100 : (opacity < 0) ? 0 : opacity;
    }
    
    void setVisible(bool visible) {visible ? this->hidden=false : this->hidden=true;}
    bool isVisible() {return !(this->hidden);}
    
    View* getChild(std::string name) {return children[name];}
    void addChild(std::string name, View* view) {this->children[name] = view;}
    
    
    // draw this view and its children
    void doDraw(sf::RenderWindow *window) {
        this->draw(window);
        
        std::tr1::unordered_map<std::string, View*>::iterator it;
        for (it = children.begin(); it != children.end(); it++) {
            (*it).second->doDraw(window);
        }
    }
    
    // update view
    virtual void update() = 0;
};

#endif
