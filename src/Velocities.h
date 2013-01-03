#ifndef VELOCITIES_H
#define VELOCITIES_H

#include <SFML/System/Vector2.hpp>
#include <da/Attribute.h>

/**
 * Holds speed vectors for moving objects.
 */
struct Velocities : public da::Attribute<Velocities> {
    sf::Vector2f speed;
    sf::Vector2f acceleration;
};

#endif
