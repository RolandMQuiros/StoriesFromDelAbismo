#ifndef PLAYERUPDATER_H
#define PLAYERUPDATER_H

#include "ColliderBehavior.h"

class PlayerUpdater : public ColliderBehavior {    
    bool isCompatible(const da::Entity &entity) const;
    void updateEntity(const da::EntityPtr &entity);
    
    void onCollisionEnter(const da::EntityPtr &entity, const da::Entity &other);
    void onCollisionStay(const da::EntityPtr &entity, const da::Entity &other);
    void onCollisionExit(const da::EntityPtr &entity, const da::Entity &other);
};

#endif
