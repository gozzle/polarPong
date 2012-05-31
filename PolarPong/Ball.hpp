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
    sf::Mutex mutex;
    
    sf::Vector2f velocity;
    float speed;
    float skewFactor;
    
public:
    Ball();
    ~Ball();
    
    sf::Transformable* getShape() const {return this->shape;}
    sf::Vector2f getPosition() {
        mutex.lock();
        sf::Vector2f ret = shape->getPosition();
        mutex.unlock();
        return ret;}
    void setSpeed(float speed) {
        mutex.lock();
        this->speed = speed;
        mutex.unlock();
    }
    void setSkewFactor(float skew) {
        mutex.lock();
        this->skewFactor = skew;
        mutex.unlock();
    }
    
    // return true if ball has crossed the edge of the court
    bool hasScored();
    // fire ball in (random?) direction
    void kickOff();
    // stop movement
    void stop();
    // do reflection
    void bounce(float offset, sf::Vector2f polarCollisionPoint);
    
    bool isWithin(const sf::Vector2f& point);
    bool isCollided(Paddle &paddle);
    void updatePosition();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
