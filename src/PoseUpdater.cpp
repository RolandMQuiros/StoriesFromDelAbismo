#include <cmath>

#include <da/MathHelper.h>

#include "Actor.h"
#include "Poses.h"
#include "Sprite.h"

#include "PoseUpdater.h"

#include "CardinalDirection.h"

bool PoseUpdater::isCompatible(const da::Entity &entity) const {
    return entity.hasAttribute<Poses>() &&
           entity.hasAttribute<Sprite>();
}

void PoseUpdater::updateEntity(const da::EntityPtr &entity) {
    // Get attribute references
    Poses &poses = entity->getAttribute<Poses>();
    
    // Early out if disabled
    if (!poses.isEnabled) {
        return;
    }
    Sprite &sprite = entity->getAttribute<Sprite>();
    
    // Update animation
    poses.time += getDelta();
    if (poses.time > poses.timePerFrame) {
        poses.time = sf::Time::Zero;
        
        if (!poses.nextFrame()) {
            finished(entity);
        }
    }
    
    // Apply to sprite
    Pose::Frame frame = poses.getFrame();
    
    sprite.setTextureRect(frame.rect);
    sprite.setOrigin(frame.origin);
}
