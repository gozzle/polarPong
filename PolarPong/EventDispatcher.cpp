//
//  MovementEventQueue.cpp
//  PolarPong
//
//  Created by Callum Chalk on 13/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "EventDispatcher.hpp"


const int EventDispatcher::FPS = 60;

bool EventDispatcher::keepGoing = true;

sf::Mutex EventDispatcher::mutex;

EventDispatcher::EventMap EventDispatcher::eventInfo;


void EventDispatcher::registerHandler(EventHandler *handler) {
    // add handler to each relevant list
    std::vector<EventWrapper::Type> types = handler->getTypes();
    std::vector<EventWrapper::Type>::const_iterator it;
    for (it = types.begin(); it < types.end(); it++) {
        // make sure this type of event exists in hash map
        if (eventInfo.count(*it) == 0) {
            // add empty struct to map
            eventInfo[*it] = EventData();
        }
        // add handler to relevant set
        EventData& data = eventInfo[*it];
        mutex.lock();
        data.handlers.insert(handler);
        data.handlersHaveChanged = true;
        mutex.unlock();
    }
}

void EventDispatcher::unregisterHandler(EventHandler *handler) {
    // remove handler from each relevant list
    std::vector<EventWrapper::Type> types = handler->getTypes();
    std::vector<EventWrapper::Type>::const_iterator it;
    for (it = types.begin(); it < types.end(); it++) {
        // make sure this type of event exists in hash map
        if (eventInfo.count(*it) == 0) {
            // no handlers or queue for this type
            break;
        }
        // remove from set of handlers
        EventData& data = eventInfo[*it];
        HandlerSet::iterator iter;
        mutex.lock();
        iter = data.handlers.find(handler);
        
        if (iter != data.handlers.end()) {
            // it exists, so erase it
            data.handlers.erase(iter);
            data.handlersHaveChanged = true;
        }
        mutex.unlock();
    }
}

void EventDispatcher::fireEvent(const EventWrapper& event) {
    // make sure this type of event exists in hash map
    EventWrapper::Type type = event.getType();
    if (eventInfo.count(type) == 0) {
        // add empty struct to map
        eventInfo[type] = EventData();
    }
    // add event to queue
    EventData& data = eventInfo[type];
    mutex.lock();
    data.eventQueue.push_back(event);
    mutex.unlock();
}

void EventDispatcher::runDispatchThread() {
    
        sf::Clock clock;
        while (EventDispatcher::keepGoing) {
            
            clock.restart();
            
            // loop through event queues, dispatching to registered handlers
            
            EventMap::iterator it;
            for (it = eventInfo.begin(); it != eventInfo.end(); it++) {
                
                EventData& data = (*it).second;
                
                mutex.lock();
                while (!data.eventQueue.empty()) {
                    EventWrapper event = data.eventQueue.front();
                    data.eventQueue.pop_front();
                
                    HandlerSet::iterator it;
                    data.handlersHaveChanged = false;
                    for (it = data.handlers.begin(); 
                         it != data.handlers.end(); it++) {
                    
                        // double check handler hasn't been unregistered
                        if (data.handlersHaveChanged) {
                            break;
                        }
                        (*it)->handleEvent(event);
                    }
                }
                mutex.unlock();
            }
            
            //sleep a little
            sf::sleep(sf::seconds(1.0/FPS) - clock.getElapsedTime());
        }
}

void EventDispatcher::stopDispachThread() {
    EventDispatcher::keepGoing = false;
}