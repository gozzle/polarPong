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
    
public:
    enum Difficulty {
        EASY =0,
        MEDIUM = 1,
        HARD = 2
    };
    
private:
    Settings(){}
    
    static sf::Vector2i resolution;
    static Difficulty diff;
    static int players;
    
public:    
    static sf::Vector2i getScreenResolution();
    static void setScreenResolution(sf::Vector2i resolution);
    static Difficulty getDifficulty();
    static void changeDifficulty();
    static int getPlayers();
    static void changePlayers();
    
};

#endif
