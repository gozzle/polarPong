//
//  Paddle.cpp
//  PolarPong
//
//  Created by Callum Chalk on 13/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Paddle.hpp"
#include "ArcShape.hpp"
#include "Settings.hpp"
#include "utils.hpp"

Paddle::Paddle(int player) : INERTIA_FACTOR(6.0) {
    this->targetVel = 0;
    this->velocity = 0;
    this->speed = 0;
    this->player = player;
    
    // bounds
    float courtRadius = Settings::getZoneRadius();
    float outerRadius = 0.98 * courtRadius;
    float angularLength = 15;
    float width = 0.02 * courtRadius;
    int numBlocks = 20;
    this->shape = new ArcShape(outerRadius, angularLength, width, numBlocks);
    ((ArcShape*)shape)->setFillColor(sf::Color::White);
    shape->setPosition(sf::Vector2f(Settings::getScreenResolution()/2));
    
}

Paddle::~Paddle() {
    delete shape;
}

void Paddle::setVelocity(int vel) {
    vel = (vel > 1) ? 1 : (vel < -1) ? -1 : vel;
    this->targetVel = vel;
}


void Paddle::setInitialPosition() {
    int numPlayers = Settings::getPlayers();
    
    float rotation = 90;
    if (numPlayers > 1) {
        int* angles = Settings::getZoneBoundaries(this->player);
        if (angles[1] == 0) {
            angles[1] = 360;
        }
        rotation = angles[0] + (angles[1] - angles[0])/2;
    }
    
    rotation -= getAngularLength()/2;
    shape->setRotation(rotation);
}

void Paddle::updatePosition() {
    // check boundaries, and only move if it's within
    int *boundaries = Settings::getZoneBoundaries(this->player);
    
    // do paddle inertia (on stopping only)
    if (targetVel == 0 && velocity != targetVel) {
        int sign = (velocity > 0) ? -1 : 1;
        velocity += sign / INERTIA_FACTOR * speed/1.0;
        
        if ((sign < 0 && velocity < 0) ||
            (sign > 0 && velocity > 0) ) {
            velocity = 0;
        }
    } else {
        velocity = targetVel;
    }
    float newRotation = shape->getRotation() + velocity * speed;
    float paddlelength = getAngularLength();
    
    if (boundaries != NULL) {
        if (boundaries[0] >= (newRotation)) {
            newRotation = boundaries[0];
        } else if (boundaries[1] <= (newRotation+paddlelength)) {
            newRotation = boundaries[1] - paddlelength;
        }
    }
    shape->setRotation(newRotation);
}

float Paddle::getAngularOffset(const sf::Vector2f &point) const {
    sf::Vector2f polar = toPolar(point - Settings::getScreenCenter());
    
    float paddleCenter = getCenterAngle();
    
    return polar.y - paddleCenter;
}

float Paddle::getCenterAngle() const {
    return shape->getRotation() + getAngularLength()/2;
}

float Paddle::getRadius() const {
    ArcShape* arShape = (ArcShape*)shape;
    return arShape->getOuterRadius() - arShape->getWidth();
}

float Paddle::getAngularLength() const {
    return ((ArcShape*)shape)->getAngularLength();
}

bool Paddle::isWithin(const sf::Vector2f &point) {
    // make polar from screen center
    sf::Vector2f polar = toPolar(point - Settings::getScreenCenter());
    
    return ((ArcShape*)shape)->isWithin(polar);
}


void Paddle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
//    states.transform *= getTransform();
    
    target.draw(*((ArcShape*)shape), states);
}