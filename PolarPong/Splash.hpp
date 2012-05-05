//
//  Splash.hpp
//  PolarPong
//
//  Created by Callum Chalk on 05/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PolarPong_Splash_hpp
#define PolarPong_Splash_hpp

#include "Viewable.hpp"

class Splash : public Viewable {
private:
    
public:
    
    Splash();
    ~Splash();
    
    // inherited methods
    
    // return false if game should exit
    bool handleEvent(sf::Event *event);
    void update();
    void draw(sf::RenderWindow *window); 
    
};

#endif
