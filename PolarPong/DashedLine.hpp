//
//  DashedLine.hpp
//  PolarPong
//
//  Created by Callum Chalk on 12/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PolarPong_DashedLine_hpp
#define PolarPong_DashedLine_hpp

#include <SFML/Graphics.hpp>
#include <vector>

class DashedLine : public sf::Transformable, public sf::Drawable {
private:
    float length;
    int numDashes;
    float dashSpacing;
    float width;
    sf::Color color;
    
    std::vector<sf::RectangleShape> dashes;
    
    void updateDashes();
    
public:
    DashedLine(float length, int numDashes, float dashSpacing=1.f, float width=1.f);
    ~DashedLine();
    
    void setLength(float length);
    void setWidth(float width);
    void setNumDashes(int numDashes);
    void setDashSpacing(float spacing);
    void setColor(const sf::Color &color);
    
    float getLength()     {return this->length;}
    int   getNumDashes()  {return this->numDashes;}
    float getWidth()      {return this->width;}
    float getDashSpacing(){return this->dashSpacing;}
    float getDashLength();
    
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
};


#endif
