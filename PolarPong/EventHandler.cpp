//
//  EventHandler.cpp
//  PolarPong
//
//  Created by Callum Chalk on 22/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "EventHandler.hpp"
#include "EventDispatcher.hpp"

EventHandler::EventHandler(int typeNum, ...) {
    va_list typeList;
    va_start(typeList, typeNum);
    
    for (int i=0; i < typeNum; i++) {
        EventWrapper::Type type = (EventWrapper::Type)va_arg(typeList,int);
        this->types.push_back(type);
    }
}

EventHandler::~EventHandler() {
    EventDispatcher::unregisterHandler(this);
}

void EventHandler::handleEvent(const EventWrapper &event) {
    void* eventPtr = event.getEvent();
    switch (event.getType()) {
        case EventWrapper::WINDOW:
            handleWindowEvent(*((sf::Event*)eventPtr));
            break;
        case EventWrapper::MOVEMENT:
            handleMovementEvent(*((MovementEvent*)eventPtr));
            break;
        case EventWrapper::ENGINE_STATE:
            handleEngineStateEvent(*((EngineStateEvent*)eventPtr));
            break;
        default:
            break;
    }
}
