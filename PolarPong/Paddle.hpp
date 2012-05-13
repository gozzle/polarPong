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
    int velocity;
    float speed;
    
    int player;
    
public:
    Paddle();
    ~Paddle();
    
    sf::Shape* getBounds() {return this->bounds;}
    void setSpeed(float speed) {this->speed = speed;}
    int getPlayer() {return this->player;}
    void setPlayer(int player) {this->player = player;}
    
    void updatePosition();
    void draw(sf::RenderWindow *window);
};

#endif
