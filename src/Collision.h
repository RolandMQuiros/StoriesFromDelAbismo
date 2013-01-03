#ifndef COLLISION_H
#define COLLISION_H

#include <SFML/System/Vector2.hpp>
#include <da/Entity.h>

struct Collision {
    enum Type {
        Enter,
        Stay,
        Exit
    } type;
    
    da::EntityRef other;
    sf::Vector2f projection;
};

#endif
