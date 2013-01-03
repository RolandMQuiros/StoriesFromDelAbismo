#include "Gravity.h"
#include "Velocities.h"
#include "GravityUpdater.h"

bool GravityUpdater::isCompatible(const da::Entity &entity) const {
    return entity.hasAttribute<Gravity>() &&
           entity.hasAttribute<Velocities>();
}

void GravityUpdater::updateEntity(const da::EntityPtr &entity) {
    Gravity &grav = entity.getAttribute<Gravity>();
    Velocities &vels = entity.getAttribute<Velocities>();
    
    vels.acceleration = grav.gravity;
}
