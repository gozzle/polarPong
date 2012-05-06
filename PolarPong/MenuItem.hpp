//
//  MenuItem.h
//  PolarPong
//
//  Created by Callum Chalk on 05/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PolarPong_MenuItem_h
#define PolarPong_MenuItem_h

#include "Viewable.hpp"
#include "MenuController.hpp"
#include <SFML/Graphics.hpp>

class MenuItem : public Viewable {
private:
    
    struct TextProperties {
        sf::Font font;
        sf::Color normalColor;
        sf::Color highlightColor;
        int fontSize;
    } props;
    
    MenuController *controller;
    std::string id;
    sf::Text text;
    
    bool highlightable;
    bool highlighted;
    
public:
    MenuItem(MenuController *controller, std::string id);
    ~MenuItem();
    
    void setText(std::string text);
    std::string getText();
    void setPosition(float x, float y);
    bool contains(float x, float y);
    bool contains(sf::Vector2f position);
    void setHighlighted(bool highlighted);
    void setHighlightable(bool highlightable);
    
    // viewable methods
    bool handleEvent(sf::Event *event);
    void update();
    void draw(sf::RenderWindow *window);
};

#endif
