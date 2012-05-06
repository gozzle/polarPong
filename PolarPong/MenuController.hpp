//
//  MenuController.hpp
//  PolarPong
//
//  Created by Callum Chalk on 05/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PolarPong_MenuController_hpp
#define PolarPong_MenuController_hpp

class MenuController {

protected:
    MenuController(){}
public:
    virtual ~MenuController() {};
    virtual bool doSelectedItem(std::string id) = 0;
};

#endif
