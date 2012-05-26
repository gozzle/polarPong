//
//  AI.cpp
//  PolarPong
//
//  Created by Callum Chalk on 22/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "AI.hpp"
#include "EventDispatcher.hpp"
#include "utils.hpp"

AI::AI(Paddle* paddle, Ball* ball) :
    myPaddle(paddle),
    theBall(ball)
{
    setPlayer(myPaddle->getPlayer());
}

AI::~AI() {
    
}


void AI::update() {
    // do AI to return required movement
    
    sf::Vector2f polarBallPos = toPolar(theBall->getPosition()-Settings::getScreenCenter());
    float ballAngle = polarBallPos.y;
    float paddleAngle = myPaddle->getCenterAngle();
    float paddleLength = myPaddle->getAngularLength();
    
    // 'laziness' to avoid jitter
    float epsilon = paddleLength * 0.2;
    
    MovementEvent::Direction direction;
    if (paddleAngle < 180) {
        if (ballAngle > (paddleAngle + epsilon) &&
            ballAngle < (paddleAngle+180 - epsilon)) {
            
            direction = MovementEvent::CLOCKWISE;
        } else if (ballAngle < (paddleAngle-epsilon) ||
                   ballAngle > (paddleAngle+180 + epsilon)) {
            
            direction = MovementEvent::ANTI_CLOCKWISE;
        } else {
            direction = MovementEvent::STOP;
        }
    } else {
        if (ballAngle > (paddleAngle + epsilon) ||
            ballAngle < (paddleAngle - 180 - epsilon)) {
            
            direction = MovementEvent::CLOCKWISE;
        } else if (ballAngle < (paddleAngle-epsilon) &&
                   ballAngle > (paddleAngle-180+epsilon)) {
            
            direction = MovementEvent::ANTI_CLOCKWISE;
        } else {
            direction = MovementEvent::STOP;
        }        
    }
    
    MovementEvent mvEvent(getPlayer(), direction);
    EventDispatcher::fireEvent(EventWrapper(&mvEvent, EventWrapper::MOVEMENT));
}


