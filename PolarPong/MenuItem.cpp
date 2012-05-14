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
    props.highlightColor = sf::Color::Red;
    props.fontSize = 30;
    
    this->text.setFont(props.font);
    this->text.setCharacterSize(props.fontSize);
    
    highlighted = false;
    highlightable = true;
    
}

MenuItem::~MenuItem() {
    EventDispatcher::unregisterWindowHandler(this);
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
    
    sf::FloatRect old = bounds;
    // make minimum buffer to bounds
    bounds.width += Settings::getScreenResolution().x / 20;
    bounds.height += Settings::getScreenResolution().y / 50;
    // center new box
    bounds.left -= (bounds.width - old.width) / 2;
    bounds.top -= (bounds.height - old.height) / 2;
    return bounds.contains(x, y);
}

bool MenuItem::contains(sf::Vector2f position) {
    return this->contains(position.x, position.y);
}

void MenuItem::setHighlighted(bool highlighted) {
    if (highlightable) {
        this->highlighted = highlighted;
        if (highlighted) {
            EventDispatcher::registerWindowHandler(this);
        } else {
            EventDispatcher::unregisterWindowHandler(this);
        }
    }
}

void MenuItem::setHighlightable(bool highlightable) {
    this->highlightable = highlightable;
}

void MenuItem::handleWindowEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonReleased) {
        controller->doSelectedItem(this->id);
    }
}

void MenuItem::update() {
    // set colour of text according to highlighted status
    sf::Color color = highlighted ? props.highlightColor : props.normalColor;
    this->text.setColor(color);
}

void MenuItem::draw(sf::RenderWindow *window) {
    window->draw(this->text);
}

