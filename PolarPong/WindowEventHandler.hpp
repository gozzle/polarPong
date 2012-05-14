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

// interface for handling sfml events
class WindowEventHandler {
    
protected:
    WindowEventHandler() {}
public:
    virtual ~WindowEventHandler() {}
    virtual void handleWindowEvent(const sf::Event& event) = 0;
};

#endif
