//
//  Engine.cpp
//  PolarPong
//
//  Created by Callum Chalk on 05/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Engine.hpp"

#include <SFML/Graphics.hpp>
#include <ctime>
#include "Splash.hpp"
#include "Level.hpp"
#include "Settings.hpp"
#include "EventDispatcher.hpp"

Engine::Engine() : EventHandler(1, EventWrapper::WINDOW),
                   activeView(NULL) {
    srand((unsigned)time(0));
    EventDispatcher::registerHandler(this);
    setState(SPLASH);
}

Engine::~Engine() {
    delete this->activeView;
    EventDispatcher::unregisterHandler(this);
    delete this->window;
}

// Hide activeView, change to new one, and show
void Engine::setState(Engine::GameState state) {
    
    Viewable *newView;
    switch (state) {
        case SPLASH:
            this->state = SPLASH;
            newView = new Splash(this);
            break;
        case GAME:
            this->state = GAME;
            newView = new Level(this);
            break;
            
        default:
            break;
    }
    if (this->activeView) {
        this->activeView->setVisible(false);
        delete this->activeView;
    }
    
    this->activeView = newView;
    this->activeView->setVisible(true);
    
}


void Engine::changeState() {
    switch (this->state) {
        case SPLASH:
            setState(GAME);
            break;
        case GAME:
            setState(SPLASH);
            break;
            
        default:
            break;
    }
                            
}

void Engine::handleWindowEvent(const sf::Event &event) {
    if (event.type == sf::Event::Closed) {
        sf::Mutex mutex;
        mutex.lock();
        this->state = QUIT;
        mutex.unlock();
    }
}

bool Engine::run() {
    bool success = true;
    
    sf::Vector2i resolution = Settings::getScreenResolution();
    window = new sf::RenderWindow(sf::VideoMode(resolution.x, resolution.y), "Polar Pong");
    window->setActive();
    window->setFramerateLimit(60);
    
    sf::RectangleShape background;
    background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    background.setFillColor(sf::Color(110,100,110));
    background.setPosition(0, 0);
    
    // set up event handling
    sf::Thread dispatchThread(&EventDispatcher::runDispatchThread);
    dispatchThread.launch();
    
    // Start game loop
    while (this->state != QUIT) {
        
        // Window event handling
        sf::Event event;
        while (window->pollEvent(event)) {
            EventDispatcher::fireEvent(EventWrapper(&event, EventWrapper::WINDOW));
        }
        
        // Updating
        this->activeView->update();
        
        // Displaying
        window->clear();
        window->draw(background);
        this->activeView->draw(window);
        window->display();
        
    }
    window->close();
    EventDispatcher::stopDispachThread();
    dispatchThread.wait();
    
    return success;
}
