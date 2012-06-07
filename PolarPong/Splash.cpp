//
//  Splash.cpp
//  PolarPong
//
//  Created by Callum Chalk on 05/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Splash.hpp"

#include "Settings.hpp"
#include "Engine.hpp"
#include "EventDispatcher.hpp"

pp::Splash::Splash() : MenuView(), EventHandler(1, EventWrapper::WINDOW) {
    
    this->setSize((sf::Vector2f)Settings::getScreenResolution());
    
    EventDispatcher::registerHandler(this);
    
    // add menu items
    mutex.lock();
    MenuItem* item = new MenuItem(this, "newGame");
    item->setText("New Game");
    addMenuItem("newGame", item);
    
    item = new MenuItem(this, "difficulty");
    item->setText(getDifficultyStr());
    addMenuItem("difficulty", item);
    
    item = new MenuItem(this, "players");
    item->setText(getPlayersStr());
    addMenuItem("players", item);
    
    item = new MenuItem(this, "diffLabel");
    item->setText("Difficulty:");
    addMenuItem("diffLabel", item);
    
    item = new MenuItem(this, "playersLabel");
    item->setText("No. Players:");
    addMenuItem("playersLabel", item);
    
    // highlightable
    ((MenuItem*)getMenuItem("diffLabel"))->setHighlightable(false);
    ((MenuItem*)getMenuItem("playersLabel"))->setHighlightable(false);
    mutex.unlock();
    
}

pp::Splash::~Splash() {
    
}

//void pp::Splash::setPositions() {
//    // position
//    sf::Vector2i res = Settings::getScreenResolution();
//    float kx = res.x / 100.f;
//    float ky = res.y / 100.f;
//    
//    sf::Vector2i center = res/2;
//    sf::Vector2i baseline = sf::Vector2i(center.x - 18*kx,
//                                         center.y - 20*ky);
//    
//    // background box
//    mutex.lock();
//    sf::RectangleShape* bgShp = (sf::RectangleShape*)((BasicShapeView*)getChild("background"))->getShape();
//    bgShp->setPosition(baseline.x - 2*kx, baseline.y - 2*ky);
//    bgShp->setSize(sf::Vector2f((center.x - baseline.x + 2*kx)*2,
//                       (center.y - baseline.y + 2*ky)*2));
//    
//    ((MenuItem*)getChild("newGame"))->setPosition(baseline.x, baseline.y);
//    ((MenuItem*)getChild("difficultyLabel"))->setPosition(baseline.x, baseline.y + 10*ky);
//    ((MenuItem*)getChild("difficulty"))->setPosition(baseline.x + 25*kx, baseline.y + 10*ky);
//    ((MenuItem*)getChild("playersLabel"))->setPosition(baseline.x, baseline.y + 20*ky);
//    ((MenuItem*)getChild("players"))->setPosition(baseline.x + 25*kx, baseline.y + 20*ky);
//    
////    newItem->setPosition(baseline.x, baseline.y +40*ky);
//    mutex.unlock();
//}

void pp::Splash::handleWindowEvent(const sf::Event& event) {
    
    // mouseMoved for highlighting
    if (event.type == sf::Event::MouseMoved) {
        sf::Vector2i mousePos = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);
        
        mutex.lock();
        if (((MenuItem*)getMenuItem("newGame"))->contains(mousePos.x, mousePos.y)) {
            ((MenuItem*)getMenuItem("newGame"))->setHighlighted(true);
            
            ((MenuItem*)getMenuItem("difficulty"))->setHighlighted(false);
            ((MenuItem*)getMenuItem("players"))->setHighlighted(false);
        } else if (((MenuItem*)getMenuItem("difficulty"))->contains(mousePos.x, mousePos.y)) {
            ((MenuItem*)getMenuItem("difficulty"))->setHighlighted(true);
            
            ((MenuItem*)getMenuItem("newGame"))->setHighlighted(false);
            ((MenuItem*)getMenuItem("players"))->setHighlighted(false);
        } else if (((MenuItem*)getMenuItem("players"))->contains(mousePos.x, mousePos.y)) {
            ((MenuItem*)getMenuItem("players"))->setHighlighted(true);
            
            ((MenuItem*)getMenuItem("newGame"))->setHighlighted(false);
            ((MenuItem*)getMenuItem("difficulty"))->setHighlighted(false);
        } else {
            ((MenuItem*)getMenuItem("newGame"))->setHighlighted(false);
            ((MenuItem*)getMenuItem("difficulty"))->setHighlighted(false);
            ((MenuItem*)getMenuItem("players"))->setHighlighted(false);
        }
        mutex.unlock();
    } else if (event.type == sf::Event::KeyReleased &&
               event.key.code == sf::Keyboard::Escape) {
        sf::Event quitEvent;
        quitEvent.type = sf::Event::Closed;
        EventDispatcher::fireEvent(EventWrapper(&quitEvent,EventWrapper::WINDOW));

    }
}

void pp::Splash::update() {
    // don't need to do anything
}

void pp::Splash::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // don't need to do anything
}

void pp::Splash::doSelectedItem(std::string id) {
    if (id == "newGame") {
        // do new game
        EngineStateEvent stateChangeEvt(EngineStateEvent::GAME);
        EventDispatcher::fireEvent(EventWrapper(&stateChangeEvt, EventWrapper::ENGINE_STATE));
    } else if (id == "difficulty") {
        // change difficulty
        Settings::changeDifficulty();
        mutex.lock();
        ((MenuItem*)getMenuItem("difficulty"))->setText(getDifficultyStr());
        mutex.unlock();
    } else if (id == "players") {
        // change number of players
        Settings::changePlayers();
        mutex.lock();
        ((MenuItem*)getMenuItem("players"))->setText(getPlayersStr());
        mutex.unlock();
    } else if (id == "quit") {
        // not button does this yet...
        sf::Event quitEvent;
        quitEvent.type = sf::Event::Closed;
        EventDispatcher::fireEvent(EventWrapper(&quitEvent, EventWrapper::WINDOW));
    }
}

std::string pp::Splash::getDifficultyStr() {
    std::string str;
    switch (Settings::getDifficulty()) {
        case Settings::EASY:
            str ="Easy";
            break;
        case Settings::MEDIUM:
            str = "Medium";
            break;
        case Settings::HARD:
            str = "Hard";
            break;
    }
    return str;
}

std::string pp::Splash::getPlayersStr() {
    char str[2];
    std::sprintf(str, "%d", Settings::getPlayers());
    return str;
}
