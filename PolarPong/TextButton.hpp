//
//  TextButton.hpp
//  PolarPong
//
//  Created by Callum Chalk on 07/06/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PolarPong_TextButton_hpp
#define PolarPong_TextButton_hpp

#include "TextView.hpp"
#include "EventHandler.hpp"
#include "EventDispatcher.hpp"
#include "Settings.hpp"

namespace pp {
    
    template <typename C> 
    class TextButton : public TextView, public EventHandler {
        
    private:
        // pointer to 'action' function
        void (C::*function)();
        // pointer to 'action' object
        C* object;
        
        bool highlighted;
        
        bool contains(sf::Vector2f point) {  
            sf::FloatRect bounds = this->getText().getGlobalBounds();
            
            sf::FloatRect old = bounds;
            // make minimum buffer to bounds
            bounds.width += Settings::getScreenResolution().x / 20;
            bounds.height += Settings::getScreenResolution().y / 50;
            // center new box
            bounds.left -= (bounds.width - old.width) / 2;
            bounds.top -= (bounds.height - old.height) / 2;
            
            // convert to true global coords
            sf::Vector2f localPos = getPosition();
            sf::Vector2f globalPos = getGlobalPosition();
            bounds.left += globalPos.x-localPos.x;
            bounds.top += globalPos.y-localPos.y;
            
            return bounds.contains(point.x, point.y);
        }
        
    public:
        
        const sf::Color DEFAULT_HIGHLIGHT_COLOR;
        
        TextButton(void(C::*function)(),C* object) : DEFAULT_HIGHLIGHT_COLOR(sf::Color::Red), EventHandler(1, EventWrapper::WINDOW) {
            
            setAction(function,object);
            highlighted = false;
            
            EventDispatcher::registerHandler(this);
        }
        TextButton(std::string text, void(C::*function)(),C* object) : DEFAULT_HIGHLIGHT_COLOR(sf::Color::Red), EventHandler(1, EventWrapper::WINDOW), TextView(text) {
            
            setAction(function,object);
            highlighted = false;
            
            EventDispatcher::registerHandler(this);
        }
        ~TextButton() {
            
        }
        
        void setAction(void(C::*function)(),C* object) {
            this->function = function;
            this->object = object;
        }
        
        void doAction() {
            (object->*function)();
        }
        
        void handleWindowEvent(const sf::Event& event) {
            if (this->contains((sf::Vector2f)sf::Mouse::getPosition())) {
                // do highlighting or action according to event
                if (event.type == sf::Event::MouseMoved) {
                    highlighted = true;
                } else if (event.type == sf::Event::MouseButtonReleased) {
                    doAction();
                }
                
            } else {
                // unhighlight, since mouse is out of button whatever the event was
                highlighted = false;
            }
        }
        
        void update() {
            // make highlighted or not
            if (highlighted) {
                this->getText().setColor(DEFAULT_HIGHLIGHT_COLOR);
            } else {
                this->getText().setColor(TextView::DEFAULT_COLOR);
            }
        }
        
        // don't need to override 'draw'
    };
}



#endif
