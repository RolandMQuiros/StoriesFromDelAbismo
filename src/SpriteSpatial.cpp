#include "SpriteSpatial.h"

da::SpatialBase *SpriteSpatial::create(da::Entity &entity) {
    if (entity.hasAttribute<Sprite>()) {
        return new SpriteSpatial(entity);
    }
    
    return NULL;
}

SpriteSpatial::SpriteSpatial(da::Entity &entity) :
da::Spatial<SpriteSpatial>(entity),
mTransform(entity.getAttribute<da::Transform>()),
mSprite(entity.getAttribute<Sprite>()) {
    
}

void SpriteSpatial::draw(sf::RenderTarget &target,
                                   sf::RenderStates states) const {
    states.transform *= mTransform.getTransform();    
    target.draw(mSprite, states);
}
