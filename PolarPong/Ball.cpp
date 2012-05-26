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

Ball::Ball() {
    mutex.lock();
    
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
    mutex.unlock();
}

Ball::~Ball() {
    mutex.lock();
    delete shape;
    mutex.unlock();
}

bool Ball::hasScored() {
    sf::Vector2i center (Settings::getScreenResolution()/2);
    mutex.lock();
    sf::Vector2f pos = shape->getPosition();
    mutex.unlock();
    int courtRadius = Settings::getZoneRadius();
    float ballRadius = toPolar(sf::Vector2f(pos.x - center.x,
                                            pos.y - center.y)).x;
    
    return ballRadius > courtRadius;
}

void Ball::kickOff() {
    float angle = (((float)rand())/RAND_MAX)* 2*M_PI;
    
    mutex.lock();
    velocity.y = speed * cos(angle);
    velocity.x = -speed * sin(angle);
    mutex.unlock();
}

void Ball::stop() {
    mutex.lock();
    this->velocity = sf::Vector2f(0,0);
    mutex.unlock();
}

void Ball::bounce(float offset, sf::Vector2f polarCollisionPoint) {
    // move ball outside paddle, to where it would be if
    // bounce happened immediately
    sf::Vector2f polarPos = toPolar(getPosition() - Settings::getScreenCenter());
    const float ballRad = ((sf::CircleShape*)shape)->getRadius();
    const float paddleRad = polarCollisionPoint.x;
    
    sf::Vector2f bouncedPos( 2*paddleRad - polarPos.x - 2 * ballRad,
                            polarPos.y);
    
    shape->setPosition(toCartesian(bouncedPos) + Settings::getScreenCenter());
    
    
    // invert direction, then modify according to skew
    // factor and offset
    sf::Vector2f polarVel = toPolar(velocity);
    
    float angleOfIncidence = polarCollisionPoint.y - polarVel.y;
    
    
    if (angleOfIncidence > 90) {
        angleOfIncidence = angleOfIncidence - 180;
    } else if (angleOfIncidence < -90) {
        angleOfIncidence = angleOfIncidence + 180;
    }
    
    float reflectionAngle = 180 - 2*angleOfIncidence;
    float skewReflectionAngle = reflectionAngle + skewFactor * offset;
    
    
    if ((reflectionAngle <=180 &&skewReflectionAngle < reflectionAngle/2) || (reflectionAngle > 180 && (180 -skewReflectionAngle) > (180 -reflectionAngle/2)) ) {
        skewReflectionAngle = reflectionAngle/2;
    }
    
    
    
    // reflect and skew
    polarVel.y -= skewReflectionAngle;
    
    mutex.lock();
    velocity = toCartesian(polarVel);
    mutex.unlock();
}

void Ball::updatePosition() {
    mutex.lock();
    shape->move(velocity.x, velocity.y);
    mutex.unlock();
}

bool Ball::isWithin(const sf::Vector2f &point) {
    mutex.lock();
    sf::Vector2f relativePos = point - shape->getPosition();
    mutex.unlock();
    float distance = sqrtf(relativePos.x*relativePos.x +
                           relativePos.y*relativePos.y);
    mutex.lock();
    if (distance < ((sf::CircleShape*)shape)->getRadius()) {
        mutex.unlock();
        return true;
    } else {
        mutex.unlock();
        return false;
    }
}

bool Ball::isCollided(Paddle &paddle) {
    
    const sf::Vector2f polarPos = toPolar(getPosition() - Settings::getScreenCenter());
    const float ballRad = ((sf::CircleShape*)shape)->getRadius();
    
    const float closeRad = 0.01 * Settings::getZoneRadius();
    if ((polarPos.x + ballRad) > (paddle.getRadius() - closeRad)) {
        const float ballRadAngle = toPolar(sf::Vector2f(-ballRad, polarPos.x)).y;
        const float closeAngle = 1.0;
        const float paddleCenter = paddle.getCenterAngle();
        
        if ( ((polarPos.y + ballRadAngle) > (paddleCenter - paddle.getAngularLength() - closeAngle)) &&
            ((polarPos.y - ballRadAngle) < (paddleCenter + paddle.getAngularLength() + closeAngle)) ) {
            
            // ball is close to paddle, so bother to do checks
            
            const int NUM_POINTS = ((sf::CircleShape*)shape)->getPointCount();
            for (int i = 0; i<NUM_POINTS; i++) {
                // check for every point on the circle shape, in global coords
                sf::Vector2f localPoint = ((sf::CircleShape*)shape)->getPoint(i);
                sf::Transform transform = shape->getTransform();
                sf::Vector2f globalPoint = transform.transformPoint(localPoint);
                
                if (paddle.isWithin(globalPoint)) {
                    return true;
                }
            }
        }
        
    }
    return false;
}

void Ball::draw(sf::RenderWindow *window) const {
    window->draw(*((sf::CircleShape*)shape));
}
