//
//  Engine.h
//  PolarPong
//
//  Created by Callum Chalk on 05/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PolarPong_Engine_h
#define PolarPong_Engine_h

#include "EventHandler.hpp"
#include "Viewable.hpp"

class Engine : public EventHandler {
private:

    enum GameState {
        SPLASH = 0,
        GAME = 1,
        QUIT
    };
    
    GameState state;
    Viewable *activeView;
    sf::RenderWindow *window;
    
    // Hide responder, change to new responder, and show the new one
    void setState(GameState);
    
public:
    Engine();
    ~Engine();
    
    // set things going
    bool run();
    
    // Call setState appropriately
    void changeState();
    
    void handleWindowEvent(const sf::Event& event);
    
};

#endif
