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
#include "EventDispatcher.hpp"
#include "utils.hpp"
#include "HumanLocal.hpp"
#include "AI.hpp"

Level::Level() : EventHandler(2, EventWrapper::WINDOW, EventWrapper::MOVEMENT) {
    
    EventDispatcher::registerHandler(this);
    
    this->reset();
}

Level::~Level() {
    deleteAll();
    
    EventDispatcher::unregisterHandler(this);
}

void Level::deleteAll() {
    mutex.lock();
    // controllers
    {
        std::vector<GameController*>::iterator it;
        for (it=gameControllers.begin(); it<gameControllers.end(); it++) {
            delete (*it);
        }
        gameControllers.clear();
    }
    
    // aiList
    aiList.clear();
    
    // ball
    if (paddles.size() > 0) {
        delete ball;
    }
    
    // paddles
    {
        std::vector<Paddle*>::iterator it;
        for (it=paddles.begin(); it<paddles.end(); it++) {
            delete (*it);
        }
        paddles.clear();
    }
    
    scores.clear();
    scoreTexts.clear();
    divisions.clear();
    
    mutex.unlock();
    
}
void Level::reset() {
    
    // delete old objects
    mutex.lock();
    deleteAll();
    
    // set up again
    
    const int numPlayers = Settings::getPlayers();
    
    // initialise scores
    mutex.lock();
    for (int i = 0; i<numPlayers; i++) {
        scores.push_back(0);
    }
    mutex.unlock();
    
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
    mutex.lock();
    courtCircle.setOrigin(RADIUS, RADIUS);
    courtCircle.setPosition(SCREEN_CENTER);
    courtCircle.setRadius(RADIUS);
    courtCircle.setPointCount(CIRCLE_POINT_COUNT);
    courtCircle.setFillColor(CIRCLE_COLOR);
    courtCircle.setOutlineThickness(LINE_WIDTHS);
    mutex.unlock();
    
    // score Texts
    for (int player = 1; player <= numPlayers; player++) {
        sf::Text scoreText(toString(scores.at(player-1)));
        scoreText.setCharacterSize(SCORE_SIZE);
        scoreText.setColor(SCORE_COLOR);
        //      scoreText.setFont(SCORE_FONT);
        sf::FloatRect bounds = scoreText.getGlobalBounds();
        bounds.width *= 0.54;
        bounds.height *= 0.9;
        scoreText.setOrigin(bounds.width, bounds.height);
        scoreText.setPosition(SCREEN_CENTER);
        
        if (numPlayers > 1) {
            int* angles = Settings::getZoneBoundaries(player);
            if (angles[1] == 0) {
                angles[1] = 360;
            }
            float rotation = angles[0] + (angles[1] - angles[0])/2;
            
            scoreText.move(toCartesian(sf::Vector2f(RADIUS/2,rotation)));
        }
        mutex.lock();
        scoreTexts.push_back(scoreText);
        mutex.unlock();
        
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
            
            mutex.lock();
            this->divisions.push_back(division);            
            mutex.unlock();
        }
    }
    
    // balls and paddles
    restart();
    
    
    mutex.unlock();
}

void Level::restart() {
    // replace ball and paddles, and set state
    
    mutex.lock();
    
    // state
    state = WAITING;
    
    // paddles
    if (paddles.size() > 0) {
        delete ball;
    }
    {
        std::vector<Paddle*>::iterator it;
        for (it = paddles.begin(); it<paddles.end(); it++) {
            delete *it;
        }
        paddles.clear();
    }
    {
        std::vector<GameController*>::iterator it;
        for (it = gameControllers.begin(); it<gameControllers.end(); it++) {
            delete *it;
        }
        gameControllers.clear();
    }
    aiList.clear();
    
    lastHitPaddle = NULL;
    const float BASE_PADDLE_SPEED = 2.0;
    int numPlayers = Settings::getPlayers();
    for (int i = 1; i<=numPlayers; i++) {
        Paddle *paddle = new Paddle();
        paddle->setPlayer(i);
        paddle->setInitialPosition();
        paddle->setSpeed(BASE_PADDLE_SPEED);
        
        paddles.push_back(paddle);
    }
    
    // ball
    ball = new Ball();
    ball->setSpeed(5);
    ball->setSkewFactor(3.0);
    
    // assign players to controllers
    for (int player = 1; player<=numPlayers; player++) {
        GameController* contrl;
        if (player == 1) {
            contrl = new HumanLocal();
        } else {
            contrl = new AI(paddles.at(player-1), ball);
            aiList.push_back((AI*)contrl);
        }
        contrl->setPlayer(player);
        
        mutex.lock();
        gameControllers.push_back(contrl);
        mutex.unlock();
    }
    
    // give new ball and paddles to AIs
    std::vector<AI*>::iterator aiIt;
    for (aiIt = aiList.begin(); aiIt < aiList.end(); aiIt++) {
        (*aiIt)->setBall(ball);
        Paddle* paddle = paddles.at((*aiIt)->getPlayer() -1);
        (*aiIt)->setPaddle(paddle);
        
        // adjust ai paddle speed according numPlayers
        paddle->setSpeed(2* BASE_PADDLE_SPEED / (numPlayers));
    }
    
    mutex.unlock();
    
}

void Level::updateScoreTexts() {
    // text
    std::vector<sf::Text>::iterator txtsIt;
    std::vector<int>::const_iterator scoresIt;
    
    mutex.lock();
    for (txtsIt = scoreTexts.begin(), scoresIt = scores.begin();
         txtsIt<scoreTexts.end(); txtsIt++, scoresIt ++) {
        
        txtsIt->setString(toString(*scoresIt));
    }
    mutex.unlock();
}

int Level::getPlayerForCoords(sf::Vector2f coords) {
    sf::Vector2i center = Settings::getScreenResolution()/2;
    coords.x -= center.x;
    coords.y -= center.y;
    sf::Vector2f polarCoords = toPolar(coords);
    int numPlayers = Settings::getPlayers();
    int player =0;
    if (numPlayers == 1) {
        player =1;
    } else {
        for (int i =1; i<=numPlayers; i++) {
            int * angles = Settings::getZoneBoundaries(i);
            
            if (angles[0] <= polarCoords.y &&
                angles[1] > polarCoords.y) {
                player = i;
                break;
            }
        }
    }
    if (player == 0) {
        throw "Error: coords are in no-one's court!";
    }
    
    return player;
}

void Level::doCollision(const Paddle& paddle) {
    // update 'last hit paddle'
    mutex.lock();
    this->lastHitPaddle = &paddle;
    mutex.unlock();
    
    // bounce ball
    sf::Vector2f ballPos = ball->getPosition();
    float offset = paddle.getAngularOffset(ballPos);
    sf::Vector2f polarCollisionPoint(paddle.getRadius(),
                                     toPolar(ballPos - Settings::getScreenCenter()).y);
    
    ball->bounce(offset, polarCollisionPoint);
}

void Level::handleWindowEvent(const sf::Event& event) {
    
    if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::Escape) {
            switch (this->state) {
                case WAITING:
                    EngineStateEvent engEvt(EngineStateEvent::SPLASH);
                    EventDispatcher::fireEvent(EventWrapper(&engEvt, EventWrapper::ENGINE_STATE));
                    break;
                case PLAYING:
                case PAUSED:
                    this->reset();
                    break;
                    
                default:
                    break;
            }
        }
    } else if (event.type == sf::Event::MouseButtonReleased) {
        switch (this->state) {
            case WAITING:
                mutex.lock();
                this->state = PLAYING;
                mutex.unlock();
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
}

void Level::handleMovementEvent(const MovementEvent& event) {
    if (this->state == PLAYING) {
        // do movement
        int player = event.getPlayer();
        MovementEvent::Direction dir = event.getDirection();
        switch (dir) {
            case MovementEvent::CLOCKWISE:
                paddles.at(player-1)->setVelocity(1);
                break;
            case MovementEvent::ANTI_CLOCKWISE:
                paddles.at(player-1)->setVelocity(-1);
                break;
            case MovementEvent::STOP:
                paddles.at(player-1)->setVelocity(0);                
                break;
                
            default:
                break;
        }
    }
}

void Level::update() {
    
    updateScoreTexts();
    
    if (state == PLAYING) {
        
        ball->updatePosition();
        
        {
            //let AIs update their paddles
            std::vector<AI*>::iterator it;
            for (it = aiList.begin(); it < aiList.end(); it++) {
                (*it)->update();
            }
        }
        
        {
            // update paddles & check collision
            std::vector<Paddle*>::iterator it;
            for (it = paddles.begin(); it < paddles.end(); it++) {
                (*it)->updatePosition();
                
                if (ball->isCollided(*(*it))) {
                    doCollision(*(*it));
                }
            }
        }
        
        // scoring
        if (ball->hasScored()) {
            int losingPlayer = this->getPlayerForCoords(ball->getPosition());
            if (lastHitPaddle != NULL) {
                // last hitter gets a point, as long as it's not gone
                // out in their own zone
                mutex.lock();
                int player = this->lastHitPaddle->getPlayer();
                scores.at(player-1) += (player == losingPlayer) ? -1 : 1;
                mutex.unlock();
            } else {
                // person who missed loses a point
                mutex.lock();
                scores.at(losingPlayer -1) -= 1;
                mutex.unlock();
            }
            
            // stop ball & paddles
            ball->stop();
            std::vector<Paddle*>::iterator it;
            for (it = paddles.begin(); it < paddles.end(); it++) {
                (*it)->setVelocity(0);
            }
            
            mutex.lock();
            state = PAUSED;
            mutex.unlock();
        }
    }
}

void Level::draw(sf::RenderWindow *window) {
    //background
    mutex.lock();
    window->draw(courtCircle);
    
    {
        // score texts
        std::vector<sf::Text>::const_iterator it;
        for (it = scoreTexts.begin(); it < scoreTexts.end(); it++) {
            window->draw(*it);
        }
    }
    
    {
        // divisions
        std::vector<DashedLine>::const_iterator it;
        for (it = divisions.begin(); it < divisions.end(); it++) {
            window->draw(*it);
        }
    }
    
    // foreground
    {
        // paddles
        std::vector<Paddle*>::const_iterator it;
        for (it = paddles.begin(); it < paddles.end(); it++) {
            (*it)->draw(window);
        }
    }
    // ball
    ball->draw(window);
    mutex.unlock();
}
