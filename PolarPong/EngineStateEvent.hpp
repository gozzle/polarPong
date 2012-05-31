//
//  EngineStateEvent.hpp
//  PolarPong
//
//  Created by Callum Chalk on 31/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PolarPong_EngineStateEvent_hpp
#define PolarPong_EngineStateEvent_hpp

#include "Event.hpp"
#include <tr1/unordered_map>

class EngineStateEvent : public Event {
public:
    enum State {
        SPLASH,
        GAME,
        QUIT
    };
    
private:
    State state;
public:
    EngineStateEvent(State state) {
        this->state=state;
    }
    EngineStateEvent(const EngineStateEvent& event) {
        this->state = event.state;
    }
    ~EngineStateEvent() {};
    
    State getState() const {return this->state;}
};

// define hash method for State
namespace std {
    namespace tr1 {
        template<>
        struct hash<typename EngineStateEvent::State> {
            inline std::size_t operator() (EngineStateEvent::State const &key) const {
                int state = key;
                return std::tr1::hash<int>()(state);
            }
        };
    }
}

#endif
