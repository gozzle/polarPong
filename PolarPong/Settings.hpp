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
    static sf::Vector2f getScreenCenter() {return sf::Vector2f(getScreenResolution()/2);}
    static void setScreenResolution(sf::Vector2i resolution);
    static Difficulty getDifficulty();
    static void changeDifficulty();
    static int getPlayers();
    static void changePlayers();
    
    
    // return two delimiting angles in degrees for the given player
    static int* getZoneBoundaries(int player);
    // return court radius
    static int getZoneRadius();
    
};

const sf::Vector2i DEFAULT_RES(1152,700);
const Settings::Difficulty DEFAULT_DIFF = Settings::MEDIUM;
const int DEFAULT_PLAYERS = 2;

#endif
