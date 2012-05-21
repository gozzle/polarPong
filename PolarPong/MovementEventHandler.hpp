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
#include "EventHandler.hpp"

// interface for handling movement events
class MovementEventHandler : public EventHandler {
    
protected:
    MovementEventHandler() :
    EventHandler(EventWrapper::MOVEMENT) {
        
    }
public:
    virtual ~MovementEventHandler() {}
    
    void handleEvent(const EventWrapper& event) {
        if (event.getType() == EventWrapper::MOVEMENT) {
            void* eventPtr = event.getEvent();
            handleMovementEvent(*((MovementEvent*)eventPtr));
        }
    }
    
    virtual void handleMovementEvent(const MovementEvent& event) = 0;
};

#endif
