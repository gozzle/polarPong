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
#include "View.hpp"

class Engine : public EventHandler {
private:
    
    EngineStateEvent::State state;
    View *activeView;
    sf::RenderWindow *window;
    
    // Hide responder, change to new responder, and show the new one
    void setState(EngineStateEvent::State state);
    
public:
    Engine();
    ~Engine();
    
    // set things going
    bool run();
    
    void handleWindowEvent(const sf::Event& event);
    void handleEngineStateEvent(const EngineStateEvent& event);
    
};

#endif
