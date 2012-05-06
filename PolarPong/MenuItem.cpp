//
//  MenuItem.cpp
//  PolarPong
//
//  Created by Callum Chalk on 05/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "MenuItem.hpp"

#include "ResourcePath.hpp"
#include "Settings.hpp"

MenuItem::MenuItem(MenuController *controller, std::string id)
{
    this->controller = controller;
    this->id = id;
    
    props.font = sf::Font::getDefaultFont();
    props.normalColor = sf::Color::White;
    props.highlightColor = sf::Color::Yellow;
    props.fontSize = 20;
    
    this->text.setFont(props.font);
    this->text.setCharacterSize(props.fontSize);
    
    highlighted = false;
    highlightable = true;
    
}

MenuItem::~MenuItem() {
    
}

void MenuItem::setText(std::string text) {
    this->text.setString(text);
}

std::string MenuItem::getText() {
    return this->text.getString();
}

void MenuItem::setPosition(float x, float y) {
    this->text.setPosition(x,y);
}

bool MenuItem::contains(float x, float y) {    
    sf::FloatRect bounds = this->text.getGlobalBounds();
    return bounds.contains(x, y);
}

bool MenuItem::contains(sf::Vector2f position) {
    return this->contains(position.x, position.y);
}

void MenuItem::setHighlighted(bool highlighted) {
    if (highlightable) {
        this->highlighted = highlighted;
    }
}

void MenuItem::setHighlightable(bool highlightable) {
    this->highlightable = highlightable;
}

bool MenuItem::handleEvent(sf::Event *event) {
    return controller->doSelectedItem(this->id);
}

void MenuItem::update() {
    // set colour of text according to highlighted status
    sf::Color color = highlighted ? props.highlightColor : props.normalColor;
    this->text.setColor(color);
}

void MenuItem::draw(sf::RenderWindow *window) {
    sf::Vector2f originalPos = this->text.getPosition();
    sf::Vector2i resolution = Settings::getScreenResolution();
    sf::Vector2f newPos = sf::Vector2f(originalPos.x * resolution.x / 100,
                                       originalPos.y * resolution.y / 100);
    this->text.setPosition(newPos);
    window->draw(this->text);
    this->text.setPosition(originalPos);
    
}

