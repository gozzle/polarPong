//
//  Splash.cpp
//  PolarPong
//
//  Created by Callum Chalk on 05/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Splash.hpp"

Splash::Splash() : Viewable(), MenuController(),
                   newGame(this, "newGame"),
                   difficulty(this, "difficulty"),
                   players(this, "difficulty")
{
    
}

Splash::~Splash() {
    
}

// return false if game should exit
bool Splash::handleEvent(sf::Event *event) {
    
    return true;
}

void Splash::update() {
    
}

void Splash::draw(sf::RenderWindow *window) {
    
}

void Splash::doSelectedItem(std::string id) {
    
}
