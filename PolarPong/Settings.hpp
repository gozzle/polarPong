//
//  Settings.hpp
//  PolarPong
//
//  Created by Callum Chalk on 05/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PolarPong_Settings_hpp
#define PolarPong_Settings_hpp

#include <SFML/System.hpp>

class Settings {
    
    static sf::Vector2i resolution;
    
public:
    
    static sf::Vector2i getScreenResolution() {return resolution;}
    static void setScreenResolution(sf::Vector2i resolution) {resolution = resolution;}
    
};

#endif
