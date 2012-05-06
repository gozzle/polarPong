//
//  Settings.cpp
//  PolarPong
//
//  Created by Callum Chalk on 06/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Settings.hpp"

sf::Vector2i Settings::resolution = sf::Vector2i(0,0);
Settings::Difficulty Settings::diff = Settings::MEDIUM;
int Settings::players = 1;

sf::Vector2i Settings::getScreenResolution() {
    return Settings::resolution;
}

void Settings::setScreenResolution(sf::Vector2i resolution) {
    Settings::resolution = resolution;
}

Settings::Difficulty Settings::getDifficulty() {
    return Settings::diff;
}

void Settings::changeDifficulty() {
    switch (Settings::diff) {
        case EASY:
            Settings::diff = MEDIUM;
            break;
        case MEDIUM:
            Settings::diff = HARD;
            break;
        case HARD:
            Settings::diff = EASY;
            break;
            
        default:
            break;
    }
}

int Settings::getPlayers() {
    return Settings::players;
}

void Settings::changePlayers() {
    // Max 4 players
    Settings::players = (Settings::players % 4) + 1;
}