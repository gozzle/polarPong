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

Paddle::Paddle(int player) {
    this->velocity = 0;
    this->speed = 0;
    this->player = player;
    
    // bounds
    float courtRadius = Settings::getZoneRadius();
    float outerRadius = 0.98 * courtRadius;
    float angularLength = 15;
    float width = 0.02 * courtRadius;
    int numBlocks = 20;
    this->bounds = new ArcShape(outerRadius, angularLength, width, numBlocks);
    ((ArcShape*)bounds)->setFillColor(sf::Color::White);
    bounds->setPosition(sf::Vector2f(Settings::getScreenResolution()/2));
    
}

Paddle::~Paddle() {
    delete bounds;
}

void Paddle::setVelocity(int vel) {
    vel = (vel > 1) ? 1 : (vel < -1) ? -1 : vel;
    this->velocity = vel;
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
    
    rotation -= ((ArcShape*)bounds)->getAngularLength()/2;
    bounds->setRotation(rotation);
}

void Paddle::updatePosition() {
    // check boundaries, and only move if it's within
    int *boundaries = Settings::getZoneBoundaries(this->player);
    float newRotation = bounds->getRotation() + velocity * speed;
    float paddlelength = ((ArcShape*)bounds)->getAngularLength();
    
    if (boundaries[0] >= (newRotation)) {
        newRotation = boundaries[0];
    } else if (boundaries[1] <= (newRotation+paddlelength)) {
        newRotation = boundaries[1] - paddlelength;
    }
    bounds->setRotation(newRotation);
}

void Paddle::draw(sf::RenderWindow *window) const{
    window->draw(*((ArcShape*)bounds));
}