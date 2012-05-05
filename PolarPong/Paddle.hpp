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
    
    sf::Vector2f position;
    
public:
    
    sf::Vector2f getPosition();
    void setPosition(float r, float theta);
};

#endif
