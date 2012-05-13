//
//  Ball.hpp
//  PolarPong
//
//  Created by Callum Chalk on 05/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PolarPong_Ball_hpp
#define PolarPong_Ball_hpp

#include "PhysicalObject.hpp"
#include "Settings.hpp"

class Ball : public PhysicalObject {
private:
    sf::Vector2f velocity;
    float speed;
    
public:
    Ball();
    ~Ball();
    
    sf::Transformable* getBounds() {return this->bounds;}
    void setSpeed(float speed) {this->speed = speed;}
    
    // return true if ball has crossed the edge of the court
    bool hasScored();
    // fire ball in (random?) direction
    void kickOff();
    // stop movement
    void stop();
    
    void updatePosition();
    void draw(sf::RenderWindow *window);
};

#endif
