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

Splash::Splash() : Viewable(), MenuController(), EventHandler(1, EventWrapper::WINDOW) {
    
    mutex.lock();
    mutex.unlock();
    
    EventDispatcher::registerHandler(this);
    
    background.setOutlineThickness(2);
    background.setFillColor(sf::Color(0,0,0,127));
    
    mutex.lock();
    newGame = new MenuItem(this, "newGame");
    difficulty = new MenuItem(this, "difficulty");
    players = new MenuItem(this, "players");
    difficultyLabel = new MenuItem(this, "diffLabel");
    playersLabel = new MenuItem(this, "playersLabel");
    
    newItem = new MenuItem(this, "newItem");
    mutex.unlock();
    
    // text
    mutex.lock();
    newGame->setText("New Game");
    difficulty->setText(getDifficultyStr());
    players->setText(getPlayersStr());
    difficultyLabel->setText("Difficulty:");
    playersLabel->setText("No. Players:");
    
    newItem->setText(" "); //weird hacked workaround to bug
    mutex.unlock();
    
    setPositions();
    
    // highlightable
    mutex.lock();
    difficultyLabel->setHighlightable(false);
    playersLabel->setHighlightable(false);
    
    newItem->setHighlightable(false);
    mutex.unlock();
    
}

Splash::~Splash() {
    mutex.lock();
    delete newGame;
    delete difficulty;
    delete players;
    delete difficultyLabel;
    delete playersLabel;
    
    delete newItem;
    mutex.unlock();
    
    EventDispatcher::unregisterHandler(this);
}

void Splash::setPositions() {
    // position
    sf::Vector2i res = Settings::getScreenResolution();
    float kx = res.x / 100.f;
    float ky = res.y / 100.f;
    
    sf::Vector2i center = res/2;
    sf::Vector2i baseline = sf::Vector2i(center.x - 18*kx,
                                         center.y - 20*ky);
    
    // background box
    mutex.lock();
    background.setPosition(baseline.x - 2*kx, baseline.y - 2*ky);
    background.setSize(sf::Vector2f((center.x - baseline.x + 2*kx)*2,
                       (center.y - baseline.y + 2*ky)*2));
    
    newGame->setPosition(baseline.x, baseline.y);
    difficultyLabel->setPosition(baseline.x, baseline.y + 10*ky);
    difficulty->setPosition(baseline.x + 25*kx, baseline.y + 10*ky);
    playersLabel->setPosition(baseline.x, baseline.y + 20*ky);
    players->setPosition(baseline.x + 25*kx, baseline.y + 20*ky);
    
    newItem->setPosition(baseline.x, baseline.y +40*ky);
    mutex.unlock();
}

void Splash::handleWindowEvent(const sf::Event& event) {
    
    // mouseMoved for highlighting
    if (event.type == sf::Event::MouseMoved) {
        sf::Vector2i mousePos = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);
        
        mutex.lock();
        if (newGame->contains(mousePos.x, mousePos.y)) {
            newGame->setHighlighted(true);
            
            difficulty->setHighlighted(false);
            players->setHighlighted(false);
        } else if (difficulty->contains(mousePos.x, mousePos.y)) {
            difficulty->setHighlighted(true);
            
            newGame->setHighlighted(false);
            players->setHighlighted(false);
        } else if (players->contains(mousePos.x, mousePos.y)) {
            players->setHighlighted(true);
            
            newGame->setHighlighted(false);
            difficulty->setHighlighted(false);
        } else {
            newGame->setHighlighted(false);
            difficulty->setHighlighted(false);
            players->setHighlighted(false);
        }
        mutex.unlock();
    } else if (event.type == sf::Event::KeyReleased &&
               event.key.code == sf::Keyboard::Escape) {
        sf::Event quitEvent;
        quitEvent.type = sf::Event::Closed;
        EventDispatcher::fireEvent(EventWrapper(&quitEvent,EventWrapper::WINDOW));

    }
}

void Splash::update() {
    
    // make sure things are in the right place
    setPositions();
    
    // update children
    mutex.lock();
    newGame->update();
    difficulty->update();
    players->update();
    difficultyLabel->update();
    playersLabel->update();
    
    newItem->update();
    mutex.unlock();
    
}

void Splash::draw(sf::RenderWindow *window) {
    
    mutex.lock();
    window->draw(background);
    
    newGame->draw(window);
    difficulty->draw(window);
    players->draw(window);
    difficultyLabel->draw(window);
    playersLabel->draw(window);
    
    newItem->draw(window);
    mutex.unlock();
    
}

void Splash::doSelectedItem(std::string id) {
    if (id == "newGame") {
        // do new game
        EngineStateEvent stateChangeEvt(EngineStateEvent::GAME);
        EventDispatcher::fireEvent(EventWrapper(&stateChangeEvt, EventWrapper::ENGINE_STATE));
    } else if (id == "difficulty") {
        // change difficulty
        Settings::changeDifficulty();
        mutex.lock();
        difficulty->setText(getDifficultyStr());
        mutex.unlock();
    } else if (id == "players") {
        // change number of players
        Settings::changePlayers();
        mutex.lock();
        players->setText(getPlayersStr());
        mutex.unlock();
    } else if (id == "quit") {
        // not button does this yet...
        sf::Event quitEvent;
        quitEvent.type = sf::Event::Closed;
        EventDispatcher::fireEvent(EventWrapper(&quitEvent, EventWrapper::WINDOW));
    }
}

std::string Splash::getDifficultyStr() {
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

std::string Splash::getPlayersStr() {
    char str[2];
    std::sprintf(str, "%d", Settings::getPlayers());
    return str;
}
