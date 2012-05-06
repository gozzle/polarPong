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

Splash::Splash(Engine *controller) : Viewable(), MenuController() {
    this->controller = controller;
    
    newGame = new MenuItem(this, "newGame");
    difficulty = new MenuItem(this, "difficulty");
    players = new MenuItem(this, "players");
    difficultyLabel = new MenuItem(this, "diffLabel");
    playersLabel = new MenuItem(this, "playersLabel");
    
    // text
    newGame->setText("New Game");
    difficulty->setText("Medium");
    players->setText("1");
    difficultyLabel->setText("Difficulty:");
    playersLabel->setText("No. Players:");
    
    setPositions();
    
    // highlightable
    difficultyLabel->setHighlightable(false);
    playersLabel->setHighlightable(false);
    
}

Splash::~Splash() {
    delete newGame;
    delete difficulty;
    delete players;
    delete difficultyLabel;
    delete playersLabel;
}

void Splash::setPositions() {
    // position
    float kx = Settings::getScreenResolution().x / 100.f;
    float ky = Settings::getScreenResolution().y / 100.f;
    
    newGame->setPosition(25*kx, 25*ky);
    difficultyLabel->setPosition(25*kx, 35*ky);
    difficulty->setPosition(50*kx, 35*ky);
    playersLabel->setPosition(25*kx, 45*ky);
    players->setPosition(50*kx, 45*ky);
}

// return false if game should exit
bool Splash::handleEvent(sf::Event *event) {
    
    static MenuItem *highlighted = NULL;
    bool keepGoing = true;
    
    // mouseMoved for highlighting
    if (event->type == sf::Event::MouseMoved) {
        sf::Vector2i mousePos = sf::Vector2i(event->mouseMove.x, event->mouseMove.y);
        
        if (newGame->contains(mousePos.x, mousePos.y)) {
            newGame->setHighlighted(true);
            highlighted = newGame;
            
            difficulty->setHighlighted(false);
            players->setHighlighted(false);
        } else if (difficulty->contains(mousePos.x, mousePos.y)) {
            difficulty->setHighlighted(true);
            highlighted = difficulty;
            
            newGame->setHighlighted(false);
            players->setHighlighted(false);
        } else if (players->contains(mousePos.x, mousePos.y)) {
            players->setHighlighted(true);
            highlighted = players;
            
            newGame->setHighlighted(false);
            difficulty->setHighlighted(false);
        } else {
            newGame->setHighlighted(false);
            difficulty->setHighlighted(false);
            players->setHighlighted(false);
            
            highlighted = NULL;
        }
    } else if (event->type == sf::Event::MouseButtonReleased &&
               highlighted != NULL) {
        keepGoing = highlighted->handleEvent(event);
        
    } else if (event->type == sf::Event::KeyReleased &&
               event->key.code == sf::Keyboard::Escape) {
        keepGoing = false;
    }
    
    return keepGoing;
}

void Splash::update() {
    
    // make sure things are in the right place
    setPositions();
    
    // update children
    newGame->update();
    difficulty->update();
    players->update();
    difficultyLabel->update();
    playersLabel->update();
    
}

void Splash::draw(sf::RenderWindow *window) {
    
    newGame->draw(window);
    difficulty->draw(window);
    players->draw(window);
    difficultyLabel->draw(window);
    playersLabel->draw(window);
    
}

// Return false if game should quit
bool Splash::doSelectedItem(std::string id) {
    bool keepGoing = true;
    
    if (id == "newGame") {
        // do new game
        this->controller->changeState();
        
    } else if (id == "difficulty") {
        // change difficulty
        Settings::changeDifficulty();
        
        switch (Settings::getDifficulty()) {
            case Settings::EASY:
                difficulty->setText("Easy");
                break;
            case Settings::MEDIUM:
                difficulty->setText("Medium");
                break;
            case Settings::HARD:
                difficulty->setText("Hard");
                break;
        }
    } else if (id == "players") {
        // change number of players
        Settings::changePlayers();
        char str[5];
        std::sprintf(str, "%d", Settings::getPlayers());
        players->setText(str);
        
    }
    
    return keepGoing;
}
