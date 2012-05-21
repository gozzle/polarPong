//
//  GameController.hpp
//  PolarPong
//
//  Created by Callum Chalk on 21/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PolarPong_GameController_hpp
#define PolarPong_GameController_hpp

class GameController {
private:
    int playerNumber;
    
protected:
    GameController() : playerNumber(1) {
        
    }
public:
    virtual ~GameController() {}
    
    int getPlayer() {return this->playerNumber;}
    void setPlayer(int player) {this->playerNumber = player;}
};

#endif
