//
//  TextView.hpp
//  PolarPong
//
//  Created by Callum Chalk on 07/06/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PolarPong_TextView_hpp
#define PolarPong_TextView_hpp

#include "View.hpp"

namespace pp {
    
    class TextView : public View {
        
    private:
        sf::Text text;
        
    public:
        TextView() {
            this->text.setColor(DEFAULT_COLOR);
            this->text.setFont(DEFAULT_FONT);
            this->text.setCharacterSize(DEFAULT_CHARACTER_SIZE);
        }
        TextView(const std::string &text) {
            this->setText(text);
            this->text.setColor(DEFAULT_COLOR);
            this->text.setFont(DEFAULT_FONT);
            this->text.setCharacterSize(DEFAULT_CHARACTER_SIZE);
        }
        ~TextView() {
            
        }
        
        std::string getTextString() {
            return this->text.getString();
        }
        
        sf::Text& getText() {
            return this->text;
        }
        
        void setText(const sf::Text &text) {
            this->text = text;
            sf::FloatRect bounds = this->text.getLocalBounds();
            this->setSize(bounds.width, bounds.height);
        }
        
        void setText(const std::string &string) {
            this->text.setString(string);
            sf::FloatRect bounds = this->text.getLocalBounds();
            this->setSize(bounds.width, bounds.height);
        }
        
        void setSize(float x, float y) {
            setSize(sf::Vector2f(x,y));
        }
        
        void setSize(sf::Vector2f size) {
            // resize text to fit within these bounds
            sf::FloatRect bounds = text.getLocalBounds();
            text.scale((size.x/bounds.width),(size.y/bounds.height));
            
            View::setSize(size);
            
        }
        
    protected:
         virtual void update() {
            // do nothing
        }
        
        void draw(sf::RenderTarget& target, sf::RenderStates states) const {
            target.draw(text, states);
        }
        
    public:
        static const sf::Color DEFAULT_COLOR;
        static const sf::Font DEFAULT_FONT;
        static const int DEFAULT_CHARACTER_SIZE;
    };
}

#endif
