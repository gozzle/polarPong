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
#include "EventDispatcher.hpp"

pp::MenuItem::MenuItem(MenuController *controller, std::string id) : EventHandler(1, EventWrapper::WINDOW)
{
    this->controller = controller;
    this->id = id;
    
    props.font = sf::Font::getDefaultFont();
    props.normalColor = sf::Color::White;
    props.highlightColor = sf::Color::Red;
    props.fontSize = 30;
    
    textMutex.lock();
    this->text.setFont(props.font);
    this->text.setCharacterSize(props.fontSize);
    textMutex.unlock();
    
    highlightMutex.lock();
    highlighted = false;
    highlightMutex.unlock();
    highlightable = true;
    
    this->setSize(0, props.fontSize);
    
}

pp::MenuItem::~MenuItem() {
    EventDispatcher::unregisterHandler(this);
}

void pp::MenuItem::setText(std::string text) {
    this->textMutex.lock();
    this->text.setString(text);
    this->setSize(this->text.getLocalBounds().width, this->text.getLocalBounds().height);
    this->textMutex.unlock();
}

std::string pp::MenuItem::getText() {
    this->textMutex.lock();
    return this->text.getString();
    this->textMutex.unlock();
}

void pp::MenuItem::setPosition(float x, float y) {
    this->text.setPosition(x,y);
}

bool pp::MenuItem::contains(float x, float y) const {    
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

bool pp::MenuItem::contains(sf::Vector2f position) const {
    return this->contains(position.x, position.y);
}

void pp::MenuItem::setHighlighted(bool highlighted) {
    if (highlightable) {
        highlightMutex.lock();
        this->highlighted = highlighted;
        if (highlighted) {
            EventDispatcher::registerHandler(this);
        } else {
            EventDispatcher::unregisterHandler(this);
        }
        this->highlightMutex.unlock();
    }
}

void pp::MenuItem::setHighlightable(bool highlightable) {
    this->highlightable = highlightable;
}

void pp::MenuItem::handleWindowEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonReleased) {
        controller->doSelectedItem(this->id);
    }
}

void pp::MenuItem::update() {
    // set colour of text according to highlighted status
    highlightMutex.lock();
    textMutex.lock();
    sf::Color color = highlighted ? props.highlightColor : props.normalColor;
    this->text.setColor(color);
    highlightMutex.unlock();
    textMutex.unlock();
}

void pp::MenuItem::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(this->text);
}

