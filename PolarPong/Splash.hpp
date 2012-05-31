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
#include "MenuController.hpp"
#include "EventHandler.hpp"

#include "MenuItem.hpp"
#include <SFML/Graphics.hpp>

class Splash : public Viewable, public MenuController, public EventHandler {
private:
    
    sf::Mutex mutex;
    
    sf::RectangleShape background;
    
    MenuItem *difficultyLabel;
    MenuItem *playersLabel;
    
    MenuItem *newGame;
    MenuItem *difficulty;
    MenuItem *players;
    MenuItem *newItem;
    
    void setPositions();
    
    std::string getDifficultyStr();
    std::string getPlayersStr();
    
public:
    
    Splash();
    ~Splash();
    
    // inherited methods
    
    void handleWindowEvent(const sf::Event& event);
    void update();
    void draw(sf::RenderWindow *window); 
    
    void doSelectedItem(std::string id);
    
};

#endif
