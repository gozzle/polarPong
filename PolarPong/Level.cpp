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
    const int LINE_WIDTHS = 2;
    const int CIRCLE_POINT_COUNT = 100; // default is 30
    const sf::Color CIRCLE_COLOR = sf::Color(0,0,0,127);
    const int DASH_SPACING = 5;
    const int NUM_DASHES = 20;
    const sf::Color DASH_COLOR = sf::Color(255,255,255,200);
    
    const int radius = Settings::getZoneRadius();
    const int numPlayers = Settings::getPlayers();
    const sf::Vector2f screenCenter(Settings::getScreenResolution()/2);
    
    // court circle
    courtCircle.setOrigin(radius, radius);
    courtCircle.setPosition(screenCenter);
    courtCircle.setRadius(radius);
    courtCircle.setPointCount(CIRCLE_POINT_COUNT);
    courtCircle.setFillColor(CIRCLE_COLOR);
    courtCircle.setOutlineThickness(LINE_WIDTHS);
    
    // divisions
    if (numPlayers > 1) {
        for (int player=1; player<=numPlayers; player++) {
            // draw dashedLine at lower boudary
            int lowerBoundAngle = Settings::getZoneBoundaries(player)[0];
            DashedLine division(radius, NUM_DASHES, DASH_SPACING, LINE_WIDTHS);
            division.setPosition(screenCenter);
            division.setOrigin(LINE_WIDTHS/2.f, -DASH_SPACING/2.f);
            division.setRotation(lowerBoundAngle);
            division.setColor(DASH_COLOR);
            
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
    window->draw(courtCircle);
    
    std::vector<DashedLine>::const_iterator it;
    for (it = divisions.begin(); it < divisions.end(); it++) {
        window->draw(*it);
    }
}
