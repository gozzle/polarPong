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
#include "Paddle.hpp"

class Ball : public PhysicalObject {
private:
    sf::Vector2f velocity;
    float speed;
    float skewFactor;
    
    bool collisionsOff;
    int frameCountDown;
    const int INITIAL_FRAME_COUNTDOWN;
    
public:
    Ball();
    ~Ball();
    
    sf::Transformable* getShape() const {return this->shape;}
    sf::Vector2f getPosition() const {return this->shape->getPosition();}
    void setSpeed(float speed) {this->speed = speed;}
    void setSkewFactor(float skew) {this->skewFactor = skew;}
    
    // return true if ball has crossed the edge of the court
    bool hasScored() const;
    // fire ball in (random?) direction
    void kickOff();
    // stop movement
    void stop();
    // do reflection
    void bounce(float offset);
    
    bool isWithin(const sf::Vector2f& point) const;
    bool isCollided(const Paddle &paddle);
    void updatePosition();
    void draw(sf::RenderWindow *window) const;
};

#endif
