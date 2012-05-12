//
//  DashedLine.cpp
//  PolarPong
//
//  Created by Callum Chalk on 12/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "DashedLine.hpp"

DashedLine::DashedLine(float length, int numDashes, float dashSpacing, float width) {
    this->length = length;
    this->numDashes = numDashes;
    this->dashSpacing = dashSpacing;
    this->width = width;
    this->color = sf::Color::White;
    float dashLength = getDashLength();
    
    // create dashes
    for (int i=0; i<numDashes; i++) {
        sf::RectangleShape dash;
        dash.setSize(sf::Vector2f(width, dashLength));
        dash.setPosition(0, i*(dashLength + dashSpacing));
        dash.setFillColor(this->color);
        
        dashes.push_back(dash);
    }
}

DashedLine::~DashedLine() {
    
}

void DashedLine::setLength(float length) {
    this->length = length;
    updateDashes();
}

void DashedLine::setWidth(float width) {
    this->width = width;
    updateDashes();
}

void DashedLine::setNumDashes(int numDashes) {
    this->numDashes = numDashes;
    updateDashes();
}

void DashedLine::setDashSpacing(float spacing) {
    this->dashSpacing = spacing;
    updateDashes();
}

void DashedLine::setColor(const sf::Color &color) {
    this->color = color;
    updateDashes();
}

void DashedLine::updateDashes() {
    sf::Vector2f newSize(this->width, getDashLength());
    sf::Color newColor = this->color;
    std::vector<sf::RectangleShape>::iterator it;
    int i;
    for (it = dashes.begin(), i=0; it < dashes.end(); it++, i++) {
        it->setSize(newSize);
        it->setPosition(0, i*(newSize.y + dashSpacing));
        it->setFillColor(newColor);
    }
}

float DashedLine::getDashLength() {
    float dashLength = (this->length / this->numDashes) - this->dashSpacing;
    return dashLength;
}

void DashedLine::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    
    states.transform *= getTransform();
    std::vector<sf::RectangleShape>::const_iterator it;
    for (it = dashes.begin(); it < dashes.end(); it++) {
        target.draw(*it, states);
    }
}
