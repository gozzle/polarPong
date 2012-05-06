//
//  Level.cpp
//  PolarPong
//
//  Created by Callum Chalk on 05/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Level.hpp"

Level::Level(Engine *controller) : Viewable() {
    this->controller = controller;
}

Level::~Level() {
    
}

// return false if game should exit
bool Level::handleEvent(sf::Event *event) {
    
    return true;
}

void Level::update() {
    
}

void Level::draw(sf::RenderWindow *window) {
    
}
