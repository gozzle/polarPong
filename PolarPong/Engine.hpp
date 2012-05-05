//
//  Engine.h
//  PolarPong
//
//  Created by Callum Chalk on 05/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PolarPong_Engine_h
#define PolarPong_Engine_h

#include "Viewable.hpp"

class Engine {
private:

    enum GameState {
        SPLASH = 0,
        GAME = 1
    };
    
    GameState state;
    Viewable *activeView;
    
    // Hide responder, change to new responder, and show the new one
    void setState(GameState);
    
public:
    Engine();
    ~Engine();
    
    // set things going
    bool run();
    
    // Call setState appropriately
    void changeState();
    
};

#endif
