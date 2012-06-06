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
#include "MenuItem.hpp"

namespace pp {
    
    class MenuView : public View {
        
    private:
        // map containing pointers to menuItems, to be able to
        // handle them as a group
        typedef std::map<std::string, MenuItem*> ItemMap;
        
        ItemMap items;
        BasicShapeView* background;
        int bgId;
        
        static sf::FloatRect DEFAULT_BOUNDS;
        static int DEFAULT_FONT_SIZE;
        static sf::Vector2f k;
        static int bgIdSeed;
        
    public:
        // create background
        MenuView();
        virtual ~MenuView();
        
        // add item to list, and to view list, if it doesn't already
        // exist in either, positioning it correctly.
        // Resize background if necessary.
        void addMenuItem(std::string name, const MenuItem* item);
        
        void removeMenuItem(std::string name);
        MenuItem* getMenuItem(std::string name);
    };
    
}

#endif
