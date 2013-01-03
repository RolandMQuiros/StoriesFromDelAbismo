#include <da/Transform.h>
#include "Velocities.h"
#include "VelocitiesUpdater.h"

bool VelocitiesUpdater::isCompatible(const da::Entity &entity) const {
    return entity.hasAttribute<da::Transform>() &&
           entity.hasAttribute<Velocities>();
}

void VelocitiesUpdater::updateEntity(const da::EntityPtr &entity) {
    da::Transform &xform = entity->getAttribute<da::Transform>();
    Velocities &vels = entity->getAttribute<Velocities>();
    
    // Apply acceleration
    vels.speed += vels.acceleration * getDelta().asSeconds();
    
    // Apply speed
    sf::Vector2f motion = vels.speed * getDelta().asSeconds();
    xform.setPosition(xform.getPosition() + motion);
}
