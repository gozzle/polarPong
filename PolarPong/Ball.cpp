//
//  Ball.cpp
//  PolarPong
//
//  Created by Callum Chalk on 12/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#define _USE_MATH_DEFINES

#include "Ball.hpp"
#include <math.h>
#include "utils.hpp"

#include <iostream>

Ball::Ball() : INITIAL_FRAME_COUNTDOWN(5){
    // collision immunity
    collisionsOff = false;
    frameCountDown = INITIAL_FRAME_COUNTDOWN;
    
    //velocity & speed
    this->speed = 0.0;
    this->velocity = sf::Vector2f(0,0);
    this->skewFactor = 1.0;
    
    // bounds
    int numPoints = 50;
    float radius = Settings::getZoneRadius() * 2.f/100;
    this->shape = new sf::CircleShape(radius, numPoints);
    ((sf::CircleShape*)shape)->setFillColor(sf::Color::White);
    shape->setOrigin(radius,radius);
    sf::Vector2i res = Settings::getScreenResolution();
    shape->setPosition(res.x/2, res.y/2);
}

Ball::~Ball() {
    delete shape;
}

bool Ball::hasScored() const {
    sf::Vector2i center (Settings::getScreenResolution()/2);
    sf::Vector2f pos = shape->getPosition();
    int courtRadius = Settings::getZoneRadius();
    float ballRadius = toPolar(sf::Vector2f(pos.x - center.x,
                                            pos.y - center.y)).x;
    
    return ballRadius > courtRadius;
}

void Ball::kickOff() {
    float angle = (((float)rand())/RAND_MAX)* 2*M_PI;
    
    velocity.y = speed * cos(angle);
    velocity.x = speed * sin(angle);
}

void Ball::stop() {
    this->velocity = sf::Vector2f(0,0);
}

void Ball::bounce(float offset) {
    // invert direction, then modify according to skew
    // factor and offset
    sf::Vector2f polarVel = toPolar(velocity);
    sf::Vector2f polarPos = toPolar(getPosition() - Settings::getScreenCenter());
    
    float angleOfIncidence = polarPos.y - polarVel.y;
    
    float reflectedAngle = 180 - 2*angleOfIncidence;
    float skewAngle = skewFactor*offset;
    
    // reflect and skew
    polarVel.y -= (reflectedAngle + skewAngle);
    
    velocity = toCartesian(polarVel);
}

void Ball::updatePosition() {
    if (collisionsOff) {
        if (--frameCountDown < 0) {
            collisionsOff = false;
            frameCountDown = INITIAL_FRAME_COUNTDOWN;
        }
    }
    shape->move(velocity.x, velocity.y);
}

bool Ball::isWithin(const sf::Vector2f &point) const {
    sf::Vector2f relativePos = point - shape->getPosition();
    float distance = sqrtf(relativePos.x*relativePos.x +
                           relativePos.y*relativePos.y);
    
    if (distance < ((sf::CircleShape*)shape)->getRadius()) {
        return true;
    } else {
        return false;
    }
}

bool Ball::isCollided(const Paddle &paddle) {
    if (!collisionsOff) {
        const sf::Vector2f polarPos = toPolar(shape->getPosition() -
                                              Settings::getScreenCenter());
        const float radius = ((sf::CircleShape*)shape)->getRadius();
        const float radiusAngle = toPolar(sf::Vector2f(radius, polarPos.x)).y;
        
        // check furthest point, and two highest-width points
        const int NUM_POINTS = 3;
        sf::Vector2f pointsToCheck[NUM_POINTS];
        pointsToCheck[0] = sf::Vector2f(polarPos.x + radius, polarPos.y);
        pointsToCheck[1] = sf::Vector2f(polarPos.x, polarPos.y + radiusAngle);
        pointsToCheck[2] = sf::Vector2f(polarPos.x, polarPos.y - radiusAngle);
        
        for (int i=0; i<NUM_POINTS; i++) {
            sf::Vector2f cartPointToCheck = toCartesian(pointsToCheck[i]) + Settings::getScreenCenter();
            
            if (paddle.isWithin(cartPointToCheck)) {
                this->collisionsOff = true;
                return true;
            } 
        }
    }
    return false;
}

void Ball::draw(sf::RenderWindow *window) const {
    window->draw(*((sf::CircleShape*)shape));
}
