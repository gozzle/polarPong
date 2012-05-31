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

#include "BasicShapeView.hpp"

pp::Splash::Splash() : View(), MenuController(), EventHandler(1, EventWrapper::WINDOW) {
    
    mutex.lock();
    mutex.unlock();
    
    EventDispatcher::registerHandler(this);
    
    sf::RectangleShape bg;
    bg.setOutlineThickness(2);
    bg.setFillColor(sf::Color(0,0,0,127));
    addChild("background", new BasicShapeView(new sf::RectangleShape(bg)));
    
    mutex.lock();
    addChild("newGame", new MenuItem(this, "newGame"));
    addChild("difficulty", new MenuItem(this, "difficulty"));
    addChild("players", new MenuItem(this, "players"));
    addChild("difficultyLabel", new MenuItem(this, "diffLabel"));
    addChild("playersLabel", new MenuItem(this, "playersLabel"));
    
    //newItem = new MenuItem(this, "newItem");
    mutex.unlock();
    
    // text
    mutex.lock();
    ((MenuItem*)getChild("newGame"))->setText("New Game");
    ((MenuItem*)getChild("difficulty"))->setText(getDifficultyStr());
    ((MenuItem*)getChild("players"))->setText(getPlayersStr());
    ((MenuItem*)getChild("difficultyLabel"))->setText("Difficulty:");
    ((MenuItem*)getChild("playersLabel"))->setText("No. Players:");
    
    //newItem->setText(" "); //weird hacked workaround to bug
    mutex.unlock();
    
    setPositions();
    
    // highlightable
    mutex.lock();
    ((MenuItem*)getChild("difficultyLabel"))->setHighlightable(false);
    ((MenuItem*)getChild("playersLabel"))->setHighlightable(false);
    
//    newItem->setHighlightable(false);
    mutex.unlock();
    
}

pp::Splash::~Splash() {
//    mutex.lock();
    
//    delete newItem;
//    mutex.unlock();
    
    EventDispatcher::unregisterHandler(this);
}

void pp::Splash::setPositions() {
    // position
    sf::Vector2i res = Settings::getScreenResolution();
    float kx = res.x / 100.f;
    float ky = res.y / 100.f;
    
    sf::Vector2i center = res/2;
    sf::Vector2i baseline = sf::Vector2i(center.x - 18*kx,
                                         center.y - 20*ky);
    
    // background box
    mutex.lock();
    sf::RectangleShape* bgShp = (sf::RectangleShape*)((BasicShapeView*)getChild("background"))->getShape();
    bgShp->setPosition(baseline.x - 2*kx, baseline.y - 2*ky);
    bgShp->setSize(sf::Vector2f((center.x - baseline.x + 2*kx)*2,
                       (center.y - baseline.y + 2*ky)*2));
    
    ((MenuItem*)getChild("newGame"))->setPosition(baseline.x, baseline.y);
    ((MenuItem*)getChild("difficultyLabel"))->setPosition(baseline.x, baseline.y + 10*ky);
    ((MenuItem*)getChild("difficulty"))->setPosition(baseline.x + 25*kx, baseline.y + 10*ky);
    ((MenuItem*)getChild("playersLabel"))->setPosition(baseline.x, baseline.y + 20*ky);
    ((MenuItem*)getChild("players"))->setPosition(baseline.x + 25*kx, baseline.y + 20*ky);
    
//    newItem->setPosition(baseline.x, baseline.y +40*ky);
    mutex.unlock();
}

void pp::Splash::handleWindowEvent(const sf::Event& event) {
    
    // mouseMoved for highlighting
    if (event.type == sf::Event::MouseMoved) {
        sf::Vector2i mousePos = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);
        
        mutex.lock();
        if (((MenuItem*)getChild("newGame"))->contains(mousePos.x, mousePos.y)) {
            ((MenuItem*)getChild("newGame"))->setHighlighted(true);
            
            ((MenuItem*)getChild("difficulty"))->setHighlighted(false);
            ((MenuItem*)getChild("players"))->setHighlighted(false);
        } else if (((MenuItem*)getChild("difficulty"))->contains(mousePos.x, mousePos.y)) {
            ((MenuItem*)getChild("difficulty"))->setHighlighted(true);
            
            ((MenuItem*)getChild("newGame"))->setHighlighted(false);
            ((MenuItem*)getChild("players"))->setHighlighted(false);
        } else if (((MenuItem*)getChild("players"))->contains(mousePos.x, mousePos.y)) {
            ((MenuItem*)getChild("players"))->setHighlighted(true);
            
            ((MenuItem*)getChild("newGame"))->setHighlighted(false);
            ((MenuItem*)getChild("difficulty"))->setHighlighted(false);
        } else {
            ((MenuItem*)getChild("newGame"))->setHighlighted(false);
            ((MenuItem*)getChild("difficulty"))->setHighlighted(false);
            ((MenuItem*)getChild("players"))->setHighlighted(false);
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
    
    mutex.lock();
    // make sure things are in the right place
    setPositions();
    
//    newItem->doUpdate();
    mutex.unlock();
    
}

void pp::Splash::draw(sf::RenderWindow *window) {
    
    mutex.lock();
    
//    newItem->doDraw(window);
    mutex.unlock();
    
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
        ((MenuItem*)getChild("difficulty"))->setText(getDifficultyStr());
        mutex.unlock();
    } else if (id == "players") {
        // change number of players
        Settings::changePlayers();
        mutex.lock();
        ((MenuItem*)getChild("players"))->setText(getPlayersStr());
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
