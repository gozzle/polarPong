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
int MenuView::DEFAULT_SPACING = 2;
int MenuView::DEFAULT_PADDING_PERCNT = 2;
sf::Vector2f MenuView::k(0,0);
int MenuView::bgIdSeed = 0;

MenuView::MenuView() {
    this->setSize((sf::Vector2f)Settings::getScreenResolution());
    
    // set up default bounds, and percentage factor
    k = ((sf::Vector2f)Settings::getScreenResolution())/100.f;
    sf::Vector2f center = Settings::getScreenCenter();
    DEFAULT_BOUNDS.left = center.x - 20*k.x;
    DEFAULT_BOUNDS.top  = center.y - 22*k.y;
    DEFAULT_BOUNDS.width= (center.x - DEFAULT_BOUNDS.left + DEFAULT_PADDING_PERCNT*k.x)*2;
    DEFAULT_BOUNDS.height=(center.y - DEFAULT_BOUNDS.top + DEFAULT_PADDING_PERCNT*k.y)*2;
    
    // set up background
    sf::RectangleShape bg;
    bg.setOutlineThickness(2);
    bg.setFillColor(sf::Color(0,0,0,127));
    bg.setSize(sf::Vector2f(DEFAULT_BOUNDS.width, DEFAULT_BOUNDS.height));
    
    // add it to lists
    bgId = bgIdSeed++;
    background = new BasicShapeView(new sf::RectangleShape(bg));
    background->setPosition(DEFAULT_BOUNDS.left, DEFAULT_BOUNDS.top);
    background->setSize(bg.getSize());
    this->addChild(("menuBG" + bgId), background);
}

MenuView::~MenuView() {
    
}

void MenuView::addMenuItem(std::string name, const View *item) {
    // if item doesn't exist in view list, add it.
    // NB. Assumes same name used here as in view list
    if (background->getChild(name) == NULL) {
        background->addChild(name, (View*)item);
    }
    // add its reference to the list of items
    View* newItem = background->getChild(name);
    items[name] = newItem;
    
    // set the new item's position
    setPosition(newItem);
    
    // readjust background size
    readjust();
}

void MenuView::removeMenuItem(std::string name) {
    // remove reference to menu item and deletes it from view list, if it exists
    if (items.count(name) > 0) {
        items.erase(name);
    }
    background->removeChild(name);
    
    // readjust background size
    readjust();
}

View* MenuView::getMenuItem(std::string name) {
    // return pointer to given menu item, or NULL if none.
    if (items.count(name) > 0) {
        return items[name];
    } else {
        return NULL;
    }
}

void MenuView::setPosition(View* item) {
    // position the (new) menu item
    int numItems = items.size() - 1;
    
    float itemsHeight = 0.0;
    ItemMap::iterator it;
    for (it = items.begin(); it != items.end(); it++) {
        itemsHeight += (*it).second->getSize().y;
    }
    itemsHeight -= item->getSize().y;
    
    item->setPosition(DEFAULT_PADDING_PERCNT*k.x,
                      DEFAULT_PADDING_PERCNT*k.y + itemsHeight + (DEFAULT_SPACING)*numItems);
}

void MenuView::readjust() {
    // resize background to fit new amount of items
    sf::Vector2f itemsSize(0,0);
    ItemMap::iterator it;
    for (it = items.begin(); it != items.end(); it++) {
        sf::Vector2f size = (*it).second->getSize();
        itemsSize.y += size.y + DEFAULT_SPACING;
        if (itemsSize.x < size.x) {
            itemsSize.x = size.x;
        }
    }
    
    if (itemsSize.x > DEFAULT_BOUNDS.width + DEFAULT_PADDING_PERCNT*k.x) {
        // re-center
        float newWidth = itemsSize.x + 2*DEFAULT_PADDING_PERCNT*k.x;
        float newX = Settings::getScreenCenter().x - newWidth/2;
        
        background->setPosition(newX, background->getPosition().y);
        background->setSize(newWidth, background->getSize().y);
        ((sf::RectangleShape*)background->getShape())->setSize(background->getSize());
    }
    if (itemsSize.y > DEFAULT_BOUNDS.height + DEFAULT_PADDING_PERCNT*k.y) {
        // extend downwards
        float newHeight = itemsSize.y + 2*DEFAULT_PADDING_PERCNT*k.y;
        
        background->setSize(background->getSize().x, newHeight);
        ((sf::RectangleShape*)background->getShape())->setSize(background->getSize());
    }
}
