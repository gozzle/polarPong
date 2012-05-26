//
//  PhysicalObject.h
//  PolarPong
//
//  Created by Callum Chalk on 05/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PolarPong_PhysicalObject_h
#define PolarPong_PhysicalObject_h

#include <SFML/Graphics.hpp>

class PhysicalObject  {
private:
    
    
protected:
    PhysicalObject() {} // makes sure it can't be instantiated
    sf::Transformable * shape;
    
public:
    virtual ~PhysicalObject() {};
    
    sf::Transformable * getShape() const {return this->shape;}
    
    // Returns true if point is within object bounds
    virtual bool isWithin(const sf::Vector2f& point) = 0;
};

#endif
