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
    //velocity & speed
    this->speed = 0.0;
    this->velocity = sf::Vector2f(0,0);
    
    // bounds
    int numPoints = 50;
    float radius = Settings::getZoneRadius() * 2.f/100;
    this->bounds = new sf::CircleShape(radius, numPoints);
    bounds->setFillColor(sf::Color::White);
    bounds->setOrigin(radius,radius);
    sf::Vector2i res = Settings::getScreenResolution();
    bounds->setPosition(res.x/2, res.y/2);
}

Ball::~Ball() {
    delete bounds;
}

bool Ball::hasScored() {
    sf::Vector2i center (Settings::getScreenResolution()/2);
    sf::Vector2f pos = bounds->getPosition();
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

void Ball::updatePosition() {
    bounds->move(velocity.x, velocity.y);
}

void Ball::draw(sf::RenderWindow *window) {
    window->draw(*bounds);
}
