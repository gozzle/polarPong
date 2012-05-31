//
//  EventHandler.hpp
//  PolarPong
//
//  Created by Callum Chalk on 15/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PolarPong_EventHandler_hpp
#define PolarPong_EventHandler_hpp

#include "EventWrapper.hpp"
#include <tr1/unordered_set>
#include <vector>
#include <stdarg.h>

class EventHandler {
    
private:
    std::vector<EventWrapper::Type> types;
    
protected:
    // subclasses must define their type on construction
    EventHandler(int typeNum, ...);
    
public:
    virtual ~EventHandler();
    
    std::vector<EventWrapper::Type> getTypes() {return this->types;}
    
    void handleEvent(const EventWrapper& event);
    
    virtual void handleWindowEvent(const sf::Event& event) {};
    virtual void handleMovementEvent(const MovementEvent& event) {};
    virtual void handleEngineStateEvent(const EngineStateEvent& event) {};
};

// define hash method for EventHandler
namespace std {
    namespace tr1 {
        template<>
        class hash<EventHandler> {
            inline std::size_t operator() (EventHandler const &key) const {
                // simply hash by object address!
                return std::tr1::hash<long>()((long)&key);
            }
        };
    }
}

#endif
