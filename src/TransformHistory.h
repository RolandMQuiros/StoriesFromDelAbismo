#ifndef TRANSFORMHISTORY_H
#define TRANSFORMHISTORY_H

#include <SFML/Graphics/Transform.hpp>
#include <da/Attribute.h>

struct TransformHistory : public da::Attribute<TransformHistory>,
                          public sf::Transformable { };

#endif
