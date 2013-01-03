#include <da/Depth.h>
#include "SpriteRenderer.h"

da::SpatialBase *SpriteRenderer::Spatial::create(da::Entity &entity) {
    if (entity.hasAttribute<Sprite>()) {
        return new Spatial(entity);
    }
    
    return NULL;
}

SpriteRenderer::Spatial::Spatial(da::Entity &entity) :
da::Spatial<Spatial>(entity),
mTransform(entity.getAttribute<da::Transform>()),
mSprite(entity.getAttribute<Sprite>()) {
    
}

void SpriteRenderer::Spatial::draw(sf::RenderTarget &target,
                                   sf::RenderStates states) const {
    states.transform *= mTransform.getTransform();
    
    target.draw(mSprite, states);
}

bool SpriteRenderer::isCompatible(const da::Entity &entity) const {
    return entity.hasAttribute<da::Transform>() &&
           entity.hasAttribute<da::Depth>() &&
           entity.hasAttribute<Sprite>();
}

void SpriteRenderer::updateEntities(da::EntityGroup &entities) {
    
}
