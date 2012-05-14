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
bool EventDispatcher::moveQueueHasChanged = false;
bool EventDispatcher::windowQueueHasChanged = false;

std::tr1::unordered_set<MovementEventHandler*> EventDispatcher::movementHandlers;
std::deque<MovementEvent> EventDispatcher::movementEvents;

std::tr1::unordered_set<WindowEventHandler*> EventDispatcher::windowHandlers;
std::deque<sf::Event> EventDispatcher::windowEvents;


void EventDispatcher::registerMovementHandler(MovementEventHandler *handler) {
    // add to set of handlers
    mutex.lock();
    EventDispatcher::movementHandlers.insert(handler);
    moveQueueHasChanged = true;
    mutex.unlock();
}

void EventDispatcher::registerWindowHandler(WindowEventHandler *handler) {
    // add to set of handlers
    mutex.lock();
    EventDispatcher::windowHandlers.insert(handler);
    windowQueueHasChanged = true;
    mutex.unlock();
}

void EventDispatcher::unregisterMovementHandler(MovementEventHandler *handler) {
    // remove from set of handlers
    std::tr1::unordered_set<MovementEventHandler*>::iterator it;
    mutex.lock();
    it = EventDispatcher::movementHandlers.find(handler);
    
    if (it != EventDispatcher::movementHandlers.end()) {
        // it exists, so erase it
        EventDispatcher::movementHandlers.erase(it);
        moveQueueHasChanged = true;
    }
    mutex.unlock();
}

void EventDispatcher::unregisterWindowHandler(WindowEventHandler *handler) {
    // remove from set of handlers
    std::tr1::unordered_set<WindowEventHandler*>::iterator it;
    mutex.lock();
    it = EventDispatcher::windowHandlers.find(handler);
    
    if (it != EventDispatcher::windowHandlers.end()) {
        // it exists, so erase it
        EventDispatcher::windowHandlers.erase(it);
        windowQueueHasChanged = true;
    }
    mutex.unlock();
}

void EventDispatcher::fireMovementEvent(const MovementEvent event) {
    // add event to queue
    mutex.lock();
    movementEvents.push_back(event);
    mutex.unlock();
}

void EventDispatcher::fireWindowEvent(const sf::Event event) {
    // add event to queue
    mutex.lock();
    windowEvents.push_back(event);
    mutex.unlock();
}

void EventDispatcher::runDispatchThread() {
    
        sf::Clock clock;
        while (EventDispatcher::keepGoing) {
            
            clock.restart();
            
            // loop through event queues, dispatching to registered handlers
            // movement
            
            
            mutex.lock();
            while (!movementEvents.empty()) {
                MovementEvent& event = movementEvents.front();
                movementEvents.pop_front();
                
                std::tr1::unordered_set<MovementEventHandler*>::iterator it;
                moveQueueHasChanged = false;
                for (it = movementHandlers.begin(); 
                     it != movementHandlers.end(); it++) {
                    
                    // double check handler hasn't been unregistered
                    if (moveQueueHasChanged) {
                        break;
                    }
                    (*it)->handleMovementEvent(event);
                }
            }
            
            // window input
            while (!windowEvents.empty()) {
                sf::Event& event = windowEvents.front();
                windowEvents.pop_front();
                
                std::tr1::unordered_set<WindowEventHandler*>::iterator it;
                windowQueueHasChanged = false;
                for (it = windowHandlers.begin();
                     it != windowHandlers.end(); it++) {
                    
                    // double check handler hasn't been unregistered
                    if (windowQueueHasChanged) {
                        break;
                    }
                    (*it)->handleWindowEvent(event);
                }
            }
            mutex.unlock();
            
            //sleep a little
            sf::sleep(sf::seconds(1.0/FPS) - clock.getElapsedTime());
        }
}

void EventDispatcher::stopDispachThread() {
    mutex.lock();
    EventDispatcher::keepGoing = false;
    mutex.unlock();
}