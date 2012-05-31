//
//  BasicShapeView.hpp
//  PolarPong
//
//  Created by Callum Chalk on 31/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PolarPong_BasicShapeView_hpp
#define PolarPong_BasicShapeView_hpp

#include "View.hpp"
#include <SFML/Graphics.hpp>

namespace pp {
    
    class BasicShapeView : public View {
    private:
        sf::Shape* shape;
        
    protected:
        // don't bother updating (can override in subclasses, eg if shape moves)
        virtual void update() {}
        
        void draw(sf::RenderWindow *window) {
            window->draw(*shape);
        }
        
    public:
        // need to ensure that users dynamically assign shape, so that this object owns it
        BasicShapeView(sf::Shape* shape) {this->shape = shape;}
        ~BasicShapeView() {delete shape;}
        
        sf::Shape* getShape() {return this->shape;}
        
    };
}

#endif
