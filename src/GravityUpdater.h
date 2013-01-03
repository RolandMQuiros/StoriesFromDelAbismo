#ifndef GRAVITYUPDATER_H
#define GRAIVTYUPDATER_H

#include <da/EntityBehavior.h>

class GravityUpdater : public da::EntityBehavior {
    bool isCompatible(const da::Entity &entity) const;
    void updateEntity(const da::EntityPtr &entity);
};

#endif
