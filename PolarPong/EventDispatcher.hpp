//
//  MovementEventQueue.hpp
//  PolarPong
//
//  Created by Callum Chalk on 13/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PolarPong_MovementEventQueue_hpp
#define PolarPong_MovementEventQueue_hpp

#import "MovementEvent.hpp"
#import "MovementEventHandler.hpp"
#import <SFML/Graphics.hpp>
#import "WindowEventHandler.hpp"
#import <tr1/unordered_set>
#import <deque>

class EventDispatcher {
private:
    // can't be instantiated or extended - static class
    EventDispatcher();
    
    // flag to stop
    static bool keepGoing;
    
    // mutex
    static sf::Mutex mutex;
    static bool moveQueueHasChanged;
    static bool windowQueueHasChanged;
    
    // target FPS
    static const int FPS;
    
    // movement events
    static std::tr1::unordered_set<MovementEventHandler*> movementHandlers;
    static std::deque<MovementEvent> movementEvents;
    
    // window(input) events
    static std::tr1::unordered_set<WindowEventHandler*> windowHandlers;
    static std::deque<sf::Event> windowEvents;
    
public:
    static void registerMovementHandler(MovementEventHandler* handler);
    static void registerWindowHandler(WindowEventHandler* handler);
    static void unregisterMovementHandler(MovementEventHandler* handler);
    static void unregisterWindowHandler(WindowEventHandler* handler);
    
    static void fireMovementEvent(const MovementEvent event);
    static void fireWindowEvent(const sf::Event event);
    
    static void runDispatchThread();
    static void stopDispachThread();
};

#endif
