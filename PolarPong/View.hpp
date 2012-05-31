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
    
//    std::tr1::unordered_map<std::string,View>
    
protected:
    // for subclass instantiation
    View() : opacity(100), hidden(true) {}
    
public:
    virtual ~View() {}
    
    // Getters & setters
    int getOpacity() {return this->opacity;}
    void setOpacity(int opacity) {
        if(opacity > 100) opacity = 100;
        if(opacity < 0) opacity = 0;
        this->opacity = opacity;
    }
    void setVisible(bool visible) {visible ? this->hidden=false : this->hidden=true;}
    bool isVisible() {return !(this->hidden);}
    
    // virtual methods
    virtual void update() = 0;
    virtual void draw(sf::RenderWindow *window) =0;
};

#endif
