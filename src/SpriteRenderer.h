#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include <SFML/Graphics/RenderTarget.hpp>

#include <da/Behavior.h>
#include <da/Spatial.h>

#include "da/Transform.h"
#include "Sprite.h"

class SpriteRenderer : public da::Behavior {
public:
    
    class Spatial : public da::Spatial<Spatial> {
    public:
        static da::SpatialBase *create(da::Entity &entity);
        
        Spatial(da::Entity &entity);
    private:
        da::Transform &mTransform;
        Sprite &mSprite;
        
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    };

private:
    
    bool isCompatible(const da::Entity &entity) const;
    void updateEntities(da::EntityGroup &entities);
};

#endif
