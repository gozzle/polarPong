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
    sf::Transformable * bounds;
    
public:
    virtual ~PhysicalObject() {};
    
    virtual sf::Transformable * getBounds() =0;
    bool isCollided(PhysicalObject *other);
};

#endif
