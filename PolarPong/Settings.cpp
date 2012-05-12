//
//  Settings.cpp
//  PolarPong
//
//  Created by Callum Chalk on 06/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Settings.hpp"

sf::Vector2i Settings::resolution = DEFAULT_RES;
Settings::Difficulty Settings::diff = DEFAULT_DIFF;
int Settings::players = DEFAULT_PLAYERS;

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

int* Settings::getZoneBoundaries(int player) {
    int *angles = new int[2];
    
    int numPlayers = Settings::getPlayers();
    
    if (player > numPlayers) {
        throw "Error: cannot have boundaries for more players than are playing";
    }
    
    if (player == 1 && numPlayers == 1) {
        // no borders
        angles = NULL;
    } else {
        angles[0] = ((player-1) * 360/numPlayers) % 360;
        angles[1] = (player   * 360/numPlayers) % 360;
    }
    
    return angles;
}

int Settings::getZoneRadius() {
    sf::Vector2i resolution = Settings::getScreenResolution();
    
    int radius = (resolution.x < resolution.y) ?
    resolution.x/2.f - (resolution.x * 2.f / 100.f) :
    resolution.y/2.f - (resolution.y * 2.f / 100.f);
    
    return radius;
}