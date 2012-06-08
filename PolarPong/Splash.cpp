//
//  Splash.cpp
//  PolarPong
//
//  Created by Callum Chalk on 05/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Splash.hpp"

#include "Settings.hpp"
#include "EventDispatcher.hpp"

#include "TextView.hpp"
#include "TextButton.hpp"

pp::Splash::Splash() : MenuView(), EventHandler(1, EventWrapper::WINDOW) {
    
    this->setSize((sf::Vector2f)Settings::getScreenResolution());
    
    EventDispatcher::registerHandler(this);
    
    // add menu items
    
    sf::Color transparent(0,0,0,0);
    sf::RectangleShape baseShp;
    baseShp.setFillColor(transparent);
    sf::Vector2f textArea = getMenuArea();
    baseShp.setSize(sf::Vector2f(textArea.x, 30));
    
    
    mutex.lock();
    // new game
    TextButton<Splash>* button = new TextButton<Splash>("New Game", &Splash::doNewGame, this);
    addMenuItem("newGame", button);
    
    // difficulty
    RectangleShapeView* box = new RectangleShapeView(new sf::RectangleShape(baseShp));
    addMenuItem("diffBox", box);
    
    TextView* label = new TextView("Difficulty:");
    box->addChild("label", label);

    button = new TextButton<Splash>(getDifficultyStr(), &Splash::doChangeDifficulty, this);
    button->setPosition(box->getSize().x/2, 0);
    box->addChild("button", button);
    
    // players
    box = new RectangleShapeView(new sf::RectangleShape(baseShp));
    addMenuItem("playerBox", box);
    
    label = new TextView("No. Players:");
    box->addChild("label", label);
    
    button = new TextButton<Splash>(getPlayersStr(), &Splash::doChangePlayers, this);
    button->setPosition(box->getSize().x/2, 0);
    box->addChild("button", button);
    
    // quit
    button = new TextButton<Splash>("Quit", &Splash::doQuit, this);
    addMenuItem("quit", button);
    
    // random testing stuff
    i = 0;
    button = new TextButton<Splash>("Add Button", &Splash::doAddButton, this);
    addMenuItem("add", button);
    
    // bug 'fixer'
    MenuItem* item = new MenuItem(this, "playersLabel2");
    item->setHighlightable(false);
    item->setText("");
    addChild("playersLabel2", item);
    
    mutex.unlock();
    
}

pp::Splash::~Splash() {
    
}

void pp::Splash::handleWindowEvent(const sf::Event& event) {
    
    if (event.type == sf::Event::KeyReleased &&
               event.key.code == sf::Keyboard::Escape) {
        doQuit();
    }
}

void pp::Splash::update() {
    // don't need to do anything
}

void pp::Splash::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // don't need to do anything
}

void pp::Splash::doNewGame() {
    EngineStateEvent stateChangeEvt(EngineStateEvent::GAME);
    EventDispatcher::fireEvent(EventWrapper(&stateChangeEvt, EventWrapper::ENGINE_STATE));
}

void pp::Splash::doChangePlayers() {
    Settings::changePlayers();
    ((TextView*)getMenuItem("playerBox")->getChild("button"))->setText(getPlayersStr());
}

void pp::Splash::doChangeDifficulty() {
    Settings::changeDifficulty();
    ((TextView*)getMenuItem("diffBox")->getChild("button"))->setText(getDifficultyStr());
}

void pp::Splash::doAddButton() {
    i++;
    
    TextButton<Splash>* button = new TextButton<Splash>("Remove Last!", &Splash::doRemoveMe, this);
    addMenuItem("remove" + this->i, button);
}

void pp::Splash::doRemoveMe() {
    removeMenuItem("remove" + this->i);
    i--;
}

void pp::Splash::doQuit() {
    sf::Event quitEvent;
    quitEvent.type = sf::Event::Closed;
    EventDispatcher::fireEvent(EventWrapper(&quitEvent, EventWrapper::WINDOW));
}

void pp::Splash::doSelectedItem(std::string id) {
    // want to get rid of this...
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
