//
//  RectangleShapeView.hpp
//  PolarPong
//
//  Created by Callum Chalk on 31/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PolarPong_RectangleShapeView_hpp
#define PolarPong_RectangleShapeView_hpp

#include "View.hpp"
#include <SFML/Graphics.hpp>

namespace pp {
    
    class RectangleShapeView : public View {
    private:
        sf::RectangleShape* shape;
        
    protected:
        // don't bother updating (can override in subclasses, eg if shape moves)
        virtual void update() {}
        
        void draw(sf::RenderTarget& target, sf::RenderStates states) const {
            target.draw(*shape, states);
        }
        
    public:
        // need to ensure that users dynamically assign shape, so that this object owns it
        RectangleShapeView(sf::RectangleShape* shape) : View(){
            this->shape = shape;
            this->setSize(shape->getSize());
        }
        ~RectangleShapeView() {delete shape;}
        
        sf::RectangleShape* getShape() {return this->shape;}
        
        void setSize(float x, float y) {
            setSize(sf::Vector2f(x,y));
        }
        
        void setSize(const sf::Vector2f& size) {
            View::setSize(size);
            this->shape->setSize(size);
        }
        
    };
}

#endif
