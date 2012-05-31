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
#include "BasicShapeView.hpp"
#include "Splash.hpp"
#include "Level.hpp"
#include "Settings.hpp"
#include "EventDispatcher.hpp"

pp::Engine::Engine() : EventHandler(2, EventWrapper::WINDOW, EventWrapper::ENGINE_STATE), activeView(NULL) {
    srand((unsigned)time(0));
    EventDispatcher::registerHandler(this);
                       
                       
    // Create background View
    sf::Vector2i res = Settings::getScreenResolution();
    sf::RectangleShape bg;
    bg.setSize(sf::Vector2f(res.x, res.y));
    bg.setFillColor(sf::Color(110,100,110));
    bg.setPosition(0, 0);
    
    this->root = new BasicShapeView(new sf::RectangleShape(bg));
    
    setState(EngineStateEvent::SPLASH);
}

pp::Engine::~Engine() {
    delete this->root;
    EventDispatcher::unregisterHandler(this);
    delete this->window;
}

// Hide activeView, change to new one, and show
void pp::Engine::setState(EngineStateEvent::State state) {
    
    root->removeChildAt(0);
    switch (state) {
        case EngineStateEvent::SPLASH:
            this->state = EngineStateEvent::SPLASH;
            root->addChild("splash", new Splash());
            
            activeView = root->getChild("splash");
            break;
        case EngineStateEvent::GAME:
            this->state = EngineStateEvent::GAME;
            root->addChild("game", new Level());
            
            activeView = root->getChild("game");
            break;
            
        default:
            break;
    }    
}

void pp::Engine::handleWindowEvent(const sf::Event &event) {
    if (event.type == sf::Event::Closed) {
        sf::Mutex mutex;
        mutex.lock();
        this->state = EngineStateEvent::QUIT;
        mutex.unlock();
    }
}

void pp::Engine::handleEngineStateEvent(const EngineStateEvent &event) {
    setState(event.getState());
}

bool pp::Engine::run() {
    bool success = true;
    
    sf::Vector2i resolution = Settings::getScreenResolution();
    window = new sf::RenderWindow(sf::VideoMode(resolution.x, resolution.y), "Polar Pong");
    window->setActive();
    window->setFramerateLimit(60);
    
    
    // set up event handling
    sf::Thread dispatchThread(&EventDispatcher::runDispatchThread);
    dispatchThread.launch();
    
    // Start game loop
    while (this->state != EngineStateEvent::QUIT) {
        
        // Window event handling
        sf::Event event;
        while (window->pollEvent(event)) {
            EventDispatcher::fireEvent(EventWrapper(&event, EventWrapper::WINDOW));
        }
        
        // Updating
        root->doUpdate();
//        this->activeView->update();
        
        // Displaying
        window->clear();
        root->doDraw(window);
        window->display();
        
    }
    window->close();
    EventDispatcher::stopDispachThread();
    dispatchThread.wait();
    
    return success;
}
