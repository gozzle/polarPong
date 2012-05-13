//
//  Level.cpp
//  PolarPong
//
//  Created by Callum Chalk on 05/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Level.hpp"
#include "Engine.hpp"
#include "Settings.hpp"
#include "utils.hpp"


Level::Level(Engine *controller) : Viewable() {
    this->controller = controller;
    
    this->reset();
}

Level::~Level() {
    delete ball;
}

void Level::reset() {
    
    // empty vectors
    scores.erase(scores.begin(), scores.end());
    scoreTexts.erase(scoreTexts.begin(), scoreTexts.end());
    divisions.erase(divisions.begin(), divisions.end());
    
    const int numPlayers = Settings::getPlayers();
    
    // initialise scores
    for (int i = 0; i<numPlayers; i++) {
        scores.push_back(0);
    }
    
    // Create background
    const int LINE_WIDTHS = 2;
    const int CIRCLE_POINT_COUNT = 100; // default is 30
    const sf::Color CIRCLE_COLOR = sf::Color(0,0,0,127);
    
    const int DASH_SPACING = 5;
    const int NUM_DASHES = 20;
    const sf::Color DASH_COLOR = sf::Color(255,255,255,200);
    
    //  const sf::Font SCORE_FONT = sf::Font::getDefaultFont();
    const int SCORE_SIZE = 50;
    const sf::Color SCORE_COLOR = DASH_COLOR;
    
    const int RADIUS = Settings::getZoneRadius();
    const sf::Vector2f SCREEN_CENTER(Settings::getScreenResolution()/2);
    
    // court circle
    courtCircle.setOrigin(RADIUS, RADIUS);
    courtCircle.setPosition(SCREEN_CENTER);
    courtCircle.setRadius(RADIUS);
    courtCircle.setPointCount(CIRCLE_POINT_COUNT);
    courtCircle.setFillColor(CIRCLE_COLOR);
    courtCircle.setOutlineThickness(LINE_WIDTHS);
    
    // score Texts
    for (int player = 1; player <= numPlayers; player++) {
        sf::Text scoreText(toString(scores.at(player-1)));
        scoreText.setCharacterSize(SCORE_SIZE);
        scoreText.setColor(SCORE_COLOR);
        //      scoreText.setFont(SCORE_FONT);
        sf::FloatRect bounds = scoreText.getGlobalBounds();
        bounds.width *= 0.54;
        bounds.height *= 0.9;
        scoreText.setOrigin(bounds.width, 2*bounds.height - RADIUS);
        scoreText.setPosition(SCREEN_CENTER);
        
        if (numPlayers > 1) {
            int* angles = Settings::getZoneBoundaries(player);
            if (angles[1] == 0) {
                angles[1] = 360;
            }
            float rotation = angles[0] + (angles[1] - angles[0])/2;
            
            scoreText.rotate(rotation);
        }
        
        scoreTexts.push_back(scoreText);
        
    }
    updateScoreTexts();
    
    // divisions
    if (numPlayers > 1) {
        for (int player=1; player<=numPlayers; player++) {
            // draw dashedLine at lower boudary
            int lowerBoundAngle = Settings::getZoneBoundaries(player)[0];
            DashedLine division(RADIUS, NUM_DASHES, DASH_SPACING, LINE_WIDTHS);
            division.setPosition(SCREEN_CENTER);
            division.setOrigin(LINE_WIDTHS/2.f, -DASH_SPACING/2.f);
            division.setRotation(lowerBoundAngle);
            division.setColor(DASH_COLOR);
            
            this->divisions.push_back(division);            
        }
    }
    
    
    // balls and paddles
    restart();
}

void Level::restart() {
    // replace ball and paddles, and set state
    
    // state
    state = WAITING;
    
    // paddles
    paddles.erase(paddles.begin(), paddles.end());
    lastHitPaddle = NULL;
    
    // ball
    ball = new Ball();
    ball->setSpeed(5);
    
}

void Level::updateScoreTexts() {
    // text
    std::vector<sf::Text>::iterator txtsIt;
    std::vector<int>::const_iterator scoresIt;
    for (txtsIt = scoreTexts.begin(), scoresIt = scores.begin();
         txtsIt<scoreTexts.end(); txtsIt++, scoresIt ++) {
        
        txtsIt->setString(toString(*scoresIt));
    }
}

int Level::getPlayerForCoords(sf::Vector2f coords) {
    sf::Vector2i center = Settings::getScreenResolution()/2;
    coords.x -= center.x;
    coords.y -= center.y;
    sf::Vector2f polarCoords = toPolar(coords);
    int numPlayers = Settings::getPlayers();
    int player =0;
    for (int i =1; i<=numPlayers; i++) {
        int * angles = Settings::getZoneBoundaries(i);
        
        if (angles[0] <= polarCoords.y &&
            angles[1] > polarCoords.y) {
            player = i;
            break;
        }
    }
    if (player == 0) {
        throw "Error: coords are in no-one's court!";
    }
    
    return player;
}

// return false if game should exit
bool Level::handleEvent(sf::Event *event) {
    bool keepGoing = true;
    
    if (event->type == sf::Event::KeyReleased) {
        if (event->key.code == sf::Keyboard::Escape) {
            switch (this->state) {
                case WAITING:
                    this->controller->changeState();
                    break;
                case PLAYING:
                case PAUSED:
                    this->reset();
                    break;
                    
                default:
                    break;
            }
        }
    } else if (event->type == sf::Event::MouseButtonReleased) {
        switch (this->state) {
            case WAITING:
                this->state = PLAYING;
                ball->kickOff();
                break;
            case PLAYING:
            case PAUSED:
                this->restart();
                break;
                
            default:
                break;
        }
    }
    
    return keepGoing;
}

void Level::update() {
    
    updateScoreTexts();
    ball->updatePosition();
    
    // scoring
    if (state == PLAYING && ball->hasScored()) {
        if (lastHitPaddle != NULL) {
            // last hitter gets a point
            int player = this->lastHitPaddle->getPlayer();
            scores.at(player-1) += 1;
        } else {
            // person who missed loses a point
            int player = this->getPlayerForCoords(ball->getBounds()->getPosition());
            scores.at(player -1) -= 1;
        }
        
        // stop ball
        ball->stop();
        state = PAUSED;
    }
}

void Level::draw(sf::RenderWindow *window) {
    //background
    window->draw(courtCircle);
    
    {
        std::vector<sf::Text>::const_iterator it;
        for (it = scoreTexts.begin(); it < scoreTexts.end(); it++) {
            window->draw(*it);
        }
    }
    
    {
        std::vector<DashedLine>::const_iterator it;
        for (it = divisions.begin(); it < divisions.end(); it++) {
            window->draw(*it);
        }
    }
    
    // foreground
    ball->draw(window);
}
