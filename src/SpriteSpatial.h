#ifndef SPRITESPATIAL_H
#define SPRITESPATIAL_H

#include <SFML/Graphics/RenderTarget.hpp>

#include <da/Transform.h>
#include <da/Spatial.h>

#include "Sprite.h"

class SpriteSpatial : public da::Spatial<SpriteSpatial> {
public:
    static da::SpatialBase *create(da::Entity &entity);
    
    SpriteSpatial(da::Entity &entity);
private:
    da::Transform &mTransform;
    Sprite &mSprite;
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

#endif
