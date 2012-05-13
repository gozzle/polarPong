//
//  ArcShape.hpp
//  PolarPong
//
//  Created by Callum Chalk on 13/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PolarPong_ArcShape_hpp
#define PolarPong_ArcShape_hpp

#include <SFML/Graphics.hpp>
#include <vector>

class ArcShape : public sf::Transformable, public sf::Drawable {
    
    float outerRadius;
    float angularLength;
    float width;
    int blockCount;
    
    sf::Color fillColor;
    
    std::vector<sf::ConvexShape> trapesiums;
    
    void refreshTrapesiums();
    
public:
    ArcShape(float radius = 0, float angularLength = 20, float width = 1, int blockCount = 30);
    ~ArcShape();
    
    float getAngularLength() {return this->angularLength;}
    
    void setFillColor(const sf::Color& color);
    sf::Color getFillColor() {return this->fillColor;}
    
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
    
};

#endif
