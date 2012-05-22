//
//  HumanLocal.hpp
//  PolarPong
//
//  Created by Callum Chalk on 21/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PolarPong_HumanLocal_hpp
#define PolarPong_HumanLocal_hpp

#include "GameController.hpp"
#include "MovementEvent.hpp"
#include "EventHandler.hpp"
#include <tr1/unordered_map>

namespace std {
    namespace tr1 {
        template<>
        struct hash<typename sf::Keyboard::Key> {
            inline std::size_t operator()(sf::Keyboard::Key const &key) const {
                int type = key;
                return std::tr1::hash<int>()(type);
            }
        };
    }
}

class HumanLocal : public GameController, public EventHandler {
    // key bindings <- make these variable at some point
    typedef std::tr1::unordered_map<sf::Keyboard::Key, MovementEvent::Direction> KeyBindings;
    
    KeyBindings bindings;
    
public:
    HumanLocal();
    ~HumanLocal();
    
    void addKeyBinding(sf::Keyboard::Key key, MovementEvent::Direction direction);
    void removeKeyBinding(const sf::Keyboard::Key &key);
    
    void handleWindowEvent(const sf::Event& event);
};

#endif
