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
    int length;
    int numDashes;
    int dashSpacing;
    int width;
    sf::Color color;
    
    std::vector<sf::RectangleShape> dashes;
    
    void updateDashes();
    
public:
    DashedLine(int length, int numDashes, int dashSpacing=1, int width=1);
    ~DashedLine();
    
    void setLength(int length);
    void setWidth(int width);
    void setNumDashes(int numDashes);
    void setDashSpacing(int spacing);
    void setColor(const sf::Color &color);
    
    int getLength()     {return this->length;}
    int getNumDashes()  {return this->numDashes;}
    int getWidth()      {return this->width;}
    int getDashSpacing(){return this->dashSpacing;}
    int getDashLength();
    
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
};


#endif
