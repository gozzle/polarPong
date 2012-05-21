//
//  WindowEventHandler.hpp
//  PolarPong
//
//  Created by Callum Chalk on 13/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PolarPong_WindowEventHandler_hpp
#define PolarPong_WindowEventHandler_hpp

#include <SFML/Graphics.hpp>
#include "EventHandler.hpp"

// interface for handling sfml events
class WindowEventHandler : public EventHandler {
    
protected:
    WindowEventHandler() :
    EventHandler(EventWrapper::WINDOW) {
        
    }
public:
    virtual ~WindowEventHandler() {}
    
    void handleEvent(const EventWrapper& event) {
        if (event.getType() == EventWrapper::WINDOW) {
            void* eventPtr = event.getEvent();
            handleWindowEvent(*((sf::Event*)eventPtr));
        }
    }
    
    virtual void handleWindowEvent(const sf::Event& event) = 0;
};

#endif
