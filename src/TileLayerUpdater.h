#ifndef TILELAYERUPDATER_H
#define TILELAYERUPDATER_H

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/View.hpp>
#include <da/EntityBehavior.h>

class TileLayerUpdater : public da::EntityBehavior {
public:
    TileLayerUpdater(sf::RenderTarget &target);

private:
    sf::RenderTarget &mTarget;
    /** Bounding box of the view, accounting for rotation */
    sf::FloatRect mViewRect;
    
    bool isCompatible(const da::Entity &entity) const;

    void beginUpdate(da::EntityGroup &entities);
    void updateEntity(const da::EntityPtr &entity);
    
};

#endif
