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

#include "MenuItem.hpp"
#include "MenuController.hpp"
#include <SFML/Graphics.hpp>

class Splash : public Viewable, public MenuController {
private:
    
    MenuItem *difficultyLabel;
    MenuItem *playersLabel;
    
    MenuItem *newGame;
    MenuItem *difficulty;
    MenuItem *players;
    
public:
    
    Splash(Engine *controller);
    ~Splash();
    
    // inherited methods
    
    // return false if game should exit
    bool handleEvent(sf::Event *event);
    void update();
    void draw(sf::RenderWindow *window); 
    
    bool doSelectedItem(std::string id);
    
};

#endif
