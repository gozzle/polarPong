//
//  AI.hpp
//  PolarPong
//
//  Created by Callum Chalk on 22/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PolarPong_AI_hpp
#define PolarPong_AI_hpp

#include "GameController.hpp"

#include "Paddle.hpp"
#include "Ball.hpp"

class AI : public GameController {
private:
    Paddle* myPaddle;
    Ball* theBall;
    
public:
    AI(Paddle* paddle, Ball* ball);
    ~AI();
    
    void setBall(Ball* ball) {this->theBall = ball;}
    void setPaddle(Paddle* paddle) {
        this->myPaddle = paddle;
        setPlayer(myPaddle->getPlayer());
    }
    
    void update();
    
};

#endif
