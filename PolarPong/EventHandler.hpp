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

class EventHandler {
    
private:
    EventWrapper::Type type;
    
protected:
    // subclasses must define their type on construction
    EventHandler(EventWrapper::Type type) {
        this->type = type;
    }
    
public:
    virtual ~EventHandler() {}
    
    EventWrapper::Type getType() {return this->type;}
    
    virtual void handleEvent(const EventWrapper& event) = 0;
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
