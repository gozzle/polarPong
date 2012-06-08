//
//  Splash.hpp
//  PolarPong
//
//  Created by Callum Chalk on 05/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PolarPong_Splash_hpp
#define PolarPong_Splash_hpp

#include "MenuView.hpp"
#include "EventHandler.hpp"

#include "MenuItem.hpp"
#include <SFML/Graphics.hpp>

namespace pp {
    
    class Splash : public MenuView, public MenuController, public EventHandler {
    private:        
        std::string getDifficultyStr();
        std::string getPlayersStr();
        
    protected:
        
        void update();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const; 
        
    public:
        
        Splash();
        ~Splash();
        
        // inherited methods
        
        void handleWindowEvent(const sf::Event& event);
        
        void doNewGame();
        void doChangePlayers();
        void doChangeDifficulty();
        
        void doRemoveMe();
        
        void doSelectedItem(std::string id);
        
    };
}

#endif
