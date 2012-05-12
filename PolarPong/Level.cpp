//
//  Level.cpp
//  PolarPong
//
//  Created by Callum Chalk on 05/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Level.hpp"
#include "Engine.hpp"

Level::Level(Engine *controller) : Viewable() {
    this->controller = controller;
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
    
}
