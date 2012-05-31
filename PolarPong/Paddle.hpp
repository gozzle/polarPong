//
//  Paddle.hpp
//  PolarPong
//
//  Created by Callum Chalk on 05/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PolarPong_Paddle_hpp
#define PolarPong_Paddle_hpp

#include "PhysicalObject.hpp"
#include <SFML/System.hpp>

class Paddle : public PhysicalObject {
private:
    const float INERTIA_FACTOR;
    int targetVel;
    float velocity;
    float speed;
    
    int player;
    
public:
    Paddle(int player=1);
    ~Paddle();
    
    void setSpeed(float speed) {this->speed = speed;}
    void setVelocity(int vel);
    int getPlayer() const {return this->player;}
    void setPlayer(int player) {this->player = player;}
    
    void setInitialPosition();
    void updatePosition();
    bool isWithin(const sf::Vector2f& point);
    float getAngularOffset(const sf::Vector2f& point) const;
    float getCenterAngle() const;
    float getRadius() const;
    float getAngularLength() const;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
