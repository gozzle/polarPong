//
//  Viewable.hpp
//  PolarPong
//
//  Created by Callum Chalk on 05/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PolarPong_Viewable_hpp
#define PolarPong_Viewable_hpp

#include <SFML/Graphics.hpp>

class Viewable {
private:
    int opacity;
    bool hidden;
    
protected:
    // for subclass instantiation
    Viewable() : opacity(100), hidden(true) {}
    
public:
    virtual ~Viewable() {};
    
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
    
    // return false if game should exit
    virtual bool handleEvent(sf::Event *event) =0;
};

#endif
