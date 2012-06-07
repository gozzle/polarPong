//
//  MovementEventQueue.hpp
//  PolarPong
//
//  Created by Callum Chalk on 13/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PolarPong_MovementEventQueue_hpp
#define PolarPong_MovementEventQueue_hpp

#include <SFML/System.hpp>
#include "EventWrapper.hpp"
#include "EventHandler.hpp"
#include <tr1/unordered_map>
#include <tr1/unordered_set>
#include <deque>

class EventDispatcher {
private:
    typedef std::tr1::unordered_set<EventHandler*> HandlerSet;
    
    // store event queue, handler set, mutex and 'hasChanged' flag for 
    //each event type, by mapping from type to struct
    struct EventData {
        EventData() : handlersHaveChanged(false){}
        EventData(const EventData& data) {
            handlersHaveChanged= data.handlersHaveChanged;
            eventQueue = data.eventQueue;
            handlers = data.handlers;
        }
        bool handlersHaveChanged;
        std::deque<EventWrapper> eventQueue;
        HandlerSet handlers;
    };
    typedef std::tr1::unordered_map<EventWrapper::Type, EventData> EventMap;
    
    // can't be instantiated or extended - static class
    EventDispatcher();
    
    // flag to stop
    static bool keepGoing;
    
    // mutex
    static sf::Mutex mutex;
    
    // target FPS
    static const int FPS;
    
    
    static EventMap eventInfo;
    
public:
    static void registerHandler(EventHandler* handler);
    static void unregisterHandler(EventHandler* handler);
    
    static void fireEvent(const EventWrapper& eventWrapper);
    
    static void runDispatchThread();
    static void stopDispachThread();
};

#endif
