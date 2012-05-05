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
    sf::Vector2f position;
    float speed;
    
public:
    Paddle();
    ~Paddle();
    
    sf::Vector2f getPosition();
    void setPosition(float r, float theta);
    
    float getSpeed() {return this->speed;}
    void setSpeed(float speed) {this->speed = speed;}
    
    bool isCollided(PhysicalObject *other);
    
};

#endif
