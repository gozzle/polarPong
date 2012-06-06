//
//  MenuView.cpp
//  PolarPong
//
//  Created by Callum Chalk on 06/06/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "MenuView.hpp"
#include "Settings.hpp"

using namespace pp;

sf::FloatRect MenuView::DEFAULT_BOUNDS(0,0,0,0);
int MenuView::DEFAULT_FONT_SIZE = 20;
sf::Vector2f k(0,0);
int MenuView::bgIdSeed = 0;

MenuView::MenuView() {
    // set up default bounds, and percentage factor
    k = ((sf::Vector2f)Settings::getScreenResolution())/100.f;
    sf::Vector2f center = Settings::getScreenCenter();
    DEFAULT_BOUNDS.left = center.x - 18*k.x;
    DEFAULT_BOUNDS.top  = center.y - 20*k.y;
    DEFAULT_BOUNDS.width= (center.x - DEFAULT_BOUNDS.left + 2*k.x)*2;
    DEFAULT_BOUNDS.height=(center.y - DEFAULT_BOUNDS.top + 2*k.y)*2;
    
    // set up background
    sf::RectangleShape bg;
    bg.setOutlineThickness(2);
    bg.setFillColor(sf::Color(0,0,0,127));
    bg.setPosition(DEFAULT_BOUNDS.left, DEFAULT_BOUNDS.top);
    bg.setSize(sf::Vector2f(DEFAULT_BOUNDS.width, DEFAULT_BOUNDS.height));
    
    // add it to lists
    bgId = bgIdSeed++;
    background = new BasicShapeView(new sf::RectangleShape(bg));
    this->addChild(("menuBG" + bgId), background);
}

MenuView::~MenuView() {
    
}

void MenuView::addMenuItem(std::string name, const pp::MenuItem *item) {
    // if item doesn't exist in view list, add it.
    // NB. Assumes same name used here as in view list
    if (this->getChild(name) != NULL) {
        this->addChild(name, (View*)item);
    }
    // add its reference to the list of items
    MenuItem* newItem = (MenuItem*)getChild(name);
    items[name] = newItem;
}

void MenuView::removeMenuItem(std::string name) {
    // remove reference to menu item and deletes it from view list, if it exists
    if (items.count(name) > 0) {
        items.erase(name);
    }
    this->removeChild(name);
}

MenuItem* MenuView::getMenuItem(std::string name) {
    // return pointer to given menu item, or NULL if none.
    if (items.count(name) > 0) {
        return items[name];
    } else {
        return NULL;
    }
}
