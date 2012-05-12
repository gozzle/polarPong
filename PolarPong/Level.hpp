//
//  Level.hpp
//  PolarPong
//
//  Created by Callum Chalk on 05/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PolarPong_Level_hpp
#define PolarPong_Level_hpp

#include "Viewable.hpp"
#include <vector>
#include "DashedLine.hpp"

class Level : public Viewable {
private:
    // Paddles
    // Ball(s?)
    // Scores
    
    // State (eg. in play, or countdown)
    
    // background: division lines and score text
    std::vector<DashedLine> divisions;
    
    
public:
    
    Level(Engine *controller);
    ~Level();
    
    // inherited methods
    
    // return false if game should exit
    bool handleEvent(sf::Event *event);
    void update();
    void draw(sf::RenderWindow *window);
    
};

#endif
