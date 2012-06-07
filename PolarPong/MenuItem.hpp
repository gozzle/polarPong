//
//  MenuItem.h
//  PolarPong
//
//  Created by Callum Chalk on 05/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PolarPong_MenuItem_h
#define PolarPong_MenuItem_h

#include "View.hpp"
#include "MenuView.hpp"
#include "EventHandler.hpp"
#include "MenuController.hpp"
#include <SFML/Graphics.hpp>


namespace pp {
    
    class MenuItem : public View, public EventHandler {
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
        
        sf::Mutex highlightMutex;
        bool highlightable;
        bool highlighted;
        
    public:
        MenuItem(MenuController *controller, std::string id);
        ~MenuItem();
        
        void setText(std::string text);
        std::string getText();
        void setPosition(float x, float y);
        bool contains(float x, float y) const;
        bool contains(sf::Vector2f position) const;
        void setHighlighted(bool highlighted);
        void setHighlightable(bool highlightable);
        
        // viewable methods
        void handleWindowEvent(const sf::Event& event);
        
    protected:
        void update();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    };
}

#endif
