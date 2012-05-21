//
//  Event.h
//  PolarPong
//
//  Created by Callum Chalk on 15/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PolarPong_EventWrapper_h
#define PolarPong_EventWrapper_h

#include <tr1/unordered_map>

#include "MovementEvent.hpp"
#include <SFML/Graphics.hpp>

class EventWrapper {
public:
    enum Type {
        MOVEMENT,
        WINDOW
    };
    
private:
    
    Type type;
    
    sf::Event* sfmlEvent;
    MovementEvent* event;
    
    void construct(void* event, Type type) {
        this->event =0;
        this->sfmlEvent=0;
        this->type = type;
        
        switch (type) {
            case MOVEMENT:
                this->event = new MovementEvent(*((MovementEvent*)event));
                break;
            case WINDOW:
                this->sfmlEvent = new sf::Event(*((sf::Event*)event));
                break;
                
            default:
                break;
        }
    }
    
    
public:
    EventWrapper(const EventWrapper& other) {
        construct(other.getEvent(), other.type);
    }
    
    EventWrapper& operator=(const EventWrapper& other) {
        construct(other.getEvent(), other.type);
        return *this;
    }
    
    // events should be fired like:
    // EventDispatcher.fireEvent(EventWrapper(movementEvent, MOVEMENT));
    EventWrapper(void* event, Type type) {
        construct(event, type);
    }
    
    ~EventWrapper() {
        delete this->event;
        this->event =0;
        delete this->sfmlEvent;
        this->sfmlEvent=0;
    }
    
    void* getEvent() const {
        switch (this->type) {
            case MOVEMENT:
                return this->event;
                break;
            case WINDOW:
                return this->sfmlEvent;
                break;
                
            default:
                break;
        }
    }
    Type getType() const {return this->type;}
};


// define hash method for Type
namespace std {
    namespace tr1 {
        template<>
        struct hash<typename EventWrapper::Type> {
            inline std::size_t operator()(EventWrapper::Type const &key) const {
                int type = key;
                return std::tr1::hash<int>()(type);
            }
        };   
    }
}

#endif
