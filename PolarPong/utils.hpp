//
//  utils.h
//
//  Created by Callum Chalk on 12/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef utils_h
#define utils_h

// taken from http://notfaq.wordpress.com/2006/08/30/c-convert-int-to-string
#include <sstream>

template <class T>
inline std::string toString(const T &t) {
    std::stringstream ss;
    ss << t;
    return ss.str();
}

#include <SFML/System.hpp>
#define _USE_MATH_DEFINES
#include <math.h>

template <class T>
inline sf::Vector2f toPolar(const sf::Vector2<T>& cart) {
    float x = cart.x;
    float y = cart.y;
    
    float r = sqrtf(x*x + y*y);
    float t = atan2f(x, y) * 180/M_PI;
    
    t += (t <= 0) ? 360 : 0;
    
    return sf::Vector2f(r,360-t);
}

template <class T>
inline sf::Vector2f toCartesian(const sf::Vector2<T>& polar) {
    float r = polar.x;
    float t = polar.y * M_PI/180;
    
    float x = r * sinf(-t);
    float y = r * cosf(-t);
    
    return sf::Vector2f(x,y);
}

#endif
