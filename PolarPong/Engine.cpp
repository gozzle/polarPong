//
//  Engine.cpp
//  PolarPong
//
//  Created by Callum Chalk on 05/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Engine.hpp"

#include <SFML/Graphics.hpp>
#include "Splash.hpp"
#include "Level.hpp"

Engine::Engine() : activeView(NULL){
    setState(SPLASH);
}

Engine::~Engine() {
    delete this->activeView;
}

// Hide activeView, change to new one, and show
void Engine::setState(Engine::GameState state) {
    
    Viewable *newView;
    switch (state) {
        case SPLASH:
            newView = new Splash();
            break;
        case GAME:
            newView = new Level();
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

bool Engine::run() {
    bool success = true;
    
    sf::RenderWindow window(sf::VideoMode(800,600), "Polar Pong");
    window.setActive();
    
    // Start game loop
    while (window.isOpen()) {
        
        // Event handling
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (!(this->activeView->handleEvent(&event))){
                window.close();
            }
        }
        
        // Updating
        this->activeView->update();
        
        // Displaying
        window.clear();
        this->activeView->draw(&window);
        window.display();
        
    }    
    
    return success;
}
