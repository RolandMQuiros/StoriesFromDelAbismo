#ifndef VELOCITIESUPDATER_H
#define VELOCITIESUPDATER_H

#include <da/EntityBehavior.h>

class VelocitiesUpdater : public da::EntityBehavior {
private:
    bool isCompatible(const da::Entity &entity) const;
    void updateEntity(const da::EntityPtr &entity);
};

#endif
