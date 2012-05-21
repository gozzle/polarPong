//
//  MovementEvent.hpp
//  PolarPong
//
//  Created by Callum Chalk on 13/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PolarPong_MovementEvent_hpp
#define PolarPong_MovementEvent_hpp

class MovementEvent {
    enum Direction {
        CLOCKWISE,
        ANTI_CLOCKWISE
    } direction;
    
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

#endif
