#ifndef DA_TRANSFORM_H
#define DA_TRANSFORM_H

#include <SFML/Graphics/Transformable.hpp>
#include "da/Attribute.h"

namespace da {

struct Transform : public da::Attribute<Transform>,
                   public sf::Transformable { };

}

#endif
