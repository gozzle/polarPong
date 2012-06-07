//
//  MenuView.hpp
//  PolarPong
//
//  Created by Callum Chalk on 01/06/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PolarPong_MenuView_hpp
#define PolarPong_MenuView_hpp

#include "View.hpp"
#include "BasicShapeView.hpp"

namespace pp {
    
    class MenuView : public View {
        
    private:
        // map containing pointers to views, to be able to
        // handle them as a group, and position them automatically
        typedef std::map<std::string, View*> ItemMap;
        
        ItemMap items;
        BasicShapeView* background;
        int bgId;
        
        static sf::FloatRect DEFAULT_BOUNDS;
        static int DEFAULT_SPACING;
        static int DEFAULT_PADDING_PERCNT;
        static sf::Vector2f k;
        static int bgIdSeed;
        
        void readjust();
        void setPosition(View* item);
        
    public:
        // create background
        MenuView();
        virtual ~MenuView();
        
        // add item to list, and to view list, if it doesn't already
        // exist in either, positioning it correctly.
        // Resize background if necessary.
        void addMenuItem(std::string name, const View* item);
        
        void removeMenuItem(std::string name);
        View* getMenuItem(std::string name);
    };
    
}

#endif
