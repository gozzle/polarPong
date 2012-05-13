//
//  ArcShape.cpp
//  PolarPong
//
//  Created by Callum Chalk on 13/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "ArcShape.hpp"
#include "utils.hpp"

ArcShape::ArcShape(float radius, float angularLength, float width, int blockCount) {
    this->outerRadius = radius;
    this->angularLength = angularLength;
    this->width = width;
    this->blockCount = blockCount;
    
    refreshTrapesiums();
}

ArcShape::~ArcShape(){
    
}

void ArcShape::refreshTrapesiums() {
    // erase old
    trapesiums.erase(trapesiums.begin(), trapesiums.end());
    
    // use instance varibles to set trapesium properties
    float offset = 0;
    float interval = angularLength / blockCount;
    for (int i = 0; i < blockCount; i++, offset+=interval) {
        sf::ConvexShape trap;
        trap.setPointCount(4);
        trap.setPoint(0, toCartesian(sf::Vector2f(outerRadius,
                                                  offset)));
        trap.setPoint(1, toCartesian(sf::Vector2f(outerRadius,
                                                  offset+interval)));
        trap.setPoint(2, toCartesian(sf::Vector2f(outerRadius - width,
                                                  offset + interval)));
        trap.setPoint(3, toCartesian(sf::Vector2f(outerRadius - width,
                                                  offset)));
        
        trapesiums.push_back(trap);
    }
}

void ArcShape::setFillColor(const sf::Color &color) {
    this->fillColor = color;
    
    std::vector<sf::ConvexShape>::iterator it;
    for (it = trapesiums.begin(); it < trapesiums.end(); it++) {
        it->setFillColor(color);
    }
}

void ArcShape::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    
    states.transform *= getTransform();
    
    std::vector<sf::ConvexShape>::const_iterator it;
    for (it = trapesiums.begin(); it < trapesiums.end(); it++) {
        target.draw(*it, states);
    }
}

