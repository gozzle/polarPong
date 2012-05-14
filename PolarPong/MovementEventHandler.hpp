//
//  MovementEventHandler.h
//  PolarPong
//
//  Created by Callum Chalk on 13/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PolarPong_MovementEventHandler_h
#define PolarPong_MovementEventHandler_h

#include "MovementEvent.hpp"

// interface for handling movement events
class MovementEventHandler {
    
protected:
    MovementEventHandler() {}
public:
    virtual ~MovementEventHandler() {}
    virtual void handleMovementEvent(const MovementEvent& event) = 0;
};

#endif
