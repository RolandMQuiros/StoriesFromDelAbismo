#include <cmath>

#include <da/Transform.h>
#include <da/MathHelper.h>

#include "Poses.h"
#include "Sprite.h"
#include "TransformHistory.h"
#include "Walker.h"

#define DELTA_THRESH 0.002f

bool Walker::isCompatible(const da::Entity &entity) const {
    return entity.hasAttribute<TransformHistory>() &&
           entity.hasAttribute<Poses>() &&
           entity.hasAttribute<Sprite>() &&
           entity.hasAttribute<da::Transform>();
}

void Walker::updateEntity(const da::EntityPtr &entity) {
    // Only update once per millisecond
    mTime += getDelta();
    if (mTime < sf::milliseconds(1)) {
        return;
    }
    mTime = sf::Time::Zero;
    
    // Get attributes
    da::Transform &xform = entity->getAttribute<da::Transform>();
    Poses &poses = entity->getAttribute<Poses>();
    Sprite &sprite = entity->getAttribute<Sprite>();
    sf::Vector2f prevPos =
        entity->getAttribute<TransformHistory>().getPosition();
    
    // Make sure they're enabled.  Early out if they're not.
    if (!poses.isEnabled || !sprite.isEnabled()) {
        return;
    }
    
    // Get change in position
    sf::Vector2f deltaPos = xform.getPosition() - prevPos;
    
    float distance = da::MathHelper::length(deltaPos.x, deltaPos.y);
    
    // Don't bother if the distance is too small.  We may regret this on the
    // magical computers of tomorrow (or if we forget to limit the framerate)
    if (distance < DELTA_THRESH) {
        return;
    }
    
    // Calculate the angle of movement.
    float angle = atan2(deltaPos.y, deltaPos.x);
    
    // atan2 yields [-pi, +pi], so let's correct it to something more palatable:
    // [0, 2pi]
    if (angle < 0.f) {
        angle += da::MathHelper::TwoPi;
    }
    
    // Threshold checking
    float center = 0.f;
    for (unsigned int i = 0; i < DirectionCount; i++) {        
        if (angle > center - da::MathHelper::PiOverEight &&
            angle <= center + da::MathHelper::PiOverEight) {
            poses.direction = (CardinalDirection)i;
            break;
        }
        
        center += da::MathHelper::PiOverFour;
    }
}
