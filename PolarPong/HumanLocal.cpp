//
//  HumanLocal.cpp
//  PolarPong
//
//  Created by Callum Chalk on 21/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "HumanLocal.hpp"
#include "EventDispatcher.hpp"

HumanLocal::HumanLocal() {
    EventDispatcher::registerHandler(this);
    
    // set up key bindings
    addKeyBinding(sf::Keyboard::Left, MovementEvent::CLOCKWISE);
    addKeyBinding(sf::Keyboard::Right, MovementEvent::ANTI_CLOCKWISE);
    
}

HumanLocal::~HumanLocal() {
    bindings.clear();
}

void HumanLocal::addKeyBinding(sf::Keyboard::Key key, MovementEvent::Direction direction) {
    
    bindings[key] = direction;
}

void HumanLocal::removeKeyBinding(const sf::Keyboard::Key &key) {
    
    bindings.erase(bindings.find(key));
}

void HumanLocal::handleWindowEvent(const sf::Event &event) {
    
    if (event.type == sf::Event::KeyPressed &&
        bindings.count(event.key.code) > 0) {
        // event is valid paddle control input
        
        // fire MovementEvent according to playerNumber and key binding
        MovementEvent mvEvent = MovementEvent(getPlayer(), bindings[event.key.code]);
        
        EventDispatcher::fireEvent(EventWrapper(&mvEvent, EventWrapper::MOVEMENT));
    }
}



