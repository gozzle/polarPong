//
//  Paddle.cpp
//  PolarPong
//
//  Created by Callum Chalk on 13/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Paddle.hpp"

Paddle::Paddle() {
    
}

Paddle::~Paddle() {
    
}


void Paddle::updatePosition() {
    // to implement
}

void Paddle::draw(sf::RenderWindow *window) {
    window->draw(*bounds);
}