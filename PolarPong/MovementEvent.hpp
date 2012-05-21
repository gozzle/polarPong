//
//  MovementEvent.hpp
//  PolarPong
//
//  Created by Callum Chalk on 13/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PolarPong_MovementEvent_hpp
#define PolarPong_MovementEvent_hpp

#include <tr1/unordered_map>

class MovementEvent {
public:
    enum Direction {
        CLOCKWISE,
        ANTI_CLOCKWISE
    } direction;
    
private:
    
    int playerNumber;
    
public:
    MovementEvent(int player, Direction direction) {
        this->playerNumber = player;
        this->direction = direction;
    }
    MovementEvent(const MovementEvent& event) {
        this->playerNumber = event.playerNumber;
        this->direction = event.direction;
    }
    ~MovementEvent() {};
    
    Direction getDirection() const {return this->direction;}
    int getPlayer() const {return this->playerNumber;}
};

// define hash method for Type
namespace std {
    namespace tr1 {
        template<>
        struct hash<typename MovementEvent::Direction> {
            inline std::size_t operator()(MovementEvent::Direction const &key) const {
                int type = key;
                return std::tr1::hash<int>()(type);
            }
        };   
    }
}

#endif
