//
//  Level.cpp
//  PolarPong
//
//  Created by Callum Chalk on 05/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Level.hpp"
#include "Engine.hpp"
#include "Settings.hpp"

Level::Level(Engine *controller) : Viewable() {
    this->controller = controller;
    
    // Create background
    int numPlayers = Settings::getPlayers();
    if (numPlayers > 1) {
        int radius = Settings::getZoneRadius();
        sf::Vector2f screenCenter(Settings::getScreenResolution()/2);
        int dashSpacing = 4;
        int numDashes = 30;
        int dashWidth = 1;
        for (int player=1; player<=numPlayers; player++) {
            // draw dashedLine at lower boudary
            int lowerBoundAngle = Settings::getZoneBoundaries(player)[0];
            DashedLine division(radius, numDashes, dashSpacing, dashWidth);
            division.setPosition(screenCenter);
            division.setOrigin(dashWidth/2.f, -dashSpacing/2.f);
            division.setRotation(lowerBoundAngle);
            
            this->divisions.push_back(division);            
        }
    }
}

Level::~Level() {
    
}

// return false if game should exit
bool Level::handleEvent(sf::Event *event) {
    bool keepGoing = true;
    
    if (event->type == sf::Event::KeyReleased) {
        if (event->key.code == sf::Keyboard::Escape) {
            this->controller->changeState();
        }
    }
    
    return keepGoing;
}

void Level::update() {
    
}

void Level::draw(sf::RenderWindow *window) {
    //background
    std::vector<DashedLine>::const_iterator it;
    for (it = divisions.begin(); it < divisions.end(); it++) {
        window->draw(*it);
    }
}
