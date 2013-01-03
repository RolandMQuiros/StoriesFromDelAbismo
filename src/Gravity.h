#ifndef GRAVITY_H
#define GRAVITY_H

#include <SFML/System/Vector2.hpp>
#include <da/Attribute.h>

struct Gravity : public da::Attribute<Gravity> {
    sf::Vector2f gravity;
};

#endif
