#include <algorithm>
#include "da/Transform.h"
#include "da/Depth.h"
#include "da/SpatialRenderer.h"

namespace da {

bool spatialLess(const std::shared_ptr<SpatialBase> &a,
                 const std::shared_ptr<SpatialBase> &b) {
    if (a && b) {
        Depth &depthA = a->getEntity().getAttribute<Depth>();
        Depth &depthB = b->getEntity().getAttribute<Depth>();
        
        return depthA < depthB;
    }
    return false;
}

SpatialRenderer::SpatialRenderer(sf::RenderTarget &target) :
mTarget(target) {
    
}

bool SpatialRenderer::isCompatible(const Entity &entity) const {
    return entity.hasAttribute<Transform>() &&
           entity.hasAttribute<Depth>();
}

void SpatialRenderer::addedEntity(const EntityRef &entity) {
    for (SpatialCreationMap::iterator iter = mRegistered.begin();
         iter != mRegistered.end(); iter++) {
        SpatialPtr spatial(iter->second(*entity.lock()));
        if (spatial) {
            mSpatials.push_back(spatial);
        }
    }
}

void SpatialRenderer::removedEntity(const EntityRef &entity) {
    EntityPtr entPtr = entity.lock();
    
    for (unsigned int i = 0; i < mSpatials.size(); i++) {
        if (mSpatials[i] && &mSpatials[i]->getEntity() == entPtr.get()) {
            mSpatials.erase(mSpatials.begin() + i--);
        }
    }
}

void SpatialRenderer::updateEntities(EntityGroup &entities) {
    std::sort(mSpatials.begin(), mSpatials.end(), spatialLess);
    
    for (unsigned int i = 0; i < mSpatials.size(); i++) {
        mTarget.draw(*mSpatials[i]);
    }
}

}
