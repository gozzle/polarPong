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
#include "EventHandler.hpp"
#include <vector>
#include "DashedLine.hpp"
#include "GameController.hpp"
#include "AI.hpp"
#include "Paddle.hpp"
#include "Ball.hpp"

class Level : public Viewable, public EventHandler {
private:
    // State (eg. in play, or countdown)
    enum State {
        WAITING,
        COUNTDOWN,
        PLAYING,
        PAUSED
    } state;
    
    sf::Mutex mutex;
    
    // Controllers
    std::vector<GameController*> gameControllers;
    // AIs
    std::vector<AI*> aiList;
    
    // Paddles
    std::vector<Paddle*> paddles;
    const Paddle *lastHitPaddle;
    // Ball(s?)
    Ball *ball;
    
    // Scores
    std::vector<int> scores;
    
    // background: division lines and score text
    sf::CircleShape courtCircle;
    std::vector<sf::Text> scoreTexts;
    std::vector<DashedLine> divisions;
    
    void updateScoreTexts();
    void reset();
    void deleteAll();
    void restart();
    
    int getPlayerForCoords(sf::Vector2f coords);
    void doCollision(const Paddle& paddle);
    
public:
    
    Level();
    ~Level();
    
    // inherited methods
    
    void handleWindowEvent(const sf::Event& event);
    void handleMovementEvent(const MovementEvent& event);
    void update();
    void draw(sf::RenderWindow *window);
    
};

#endif
