#include <da/Transform.h>
#include "TransformHistory.h"
#include "TransformHistorian.h"

TransformHistorian::TransformHistorian() { }

TransformHistorian::TransformHistorian(const sf::Time &interval) :
mInterval(interval) { }

void TransformHistorian::setInterval(const sf::Time &interval) {
    mInterval = interval;
}

sf::Time TransformHistorian::getInterval() const {
    return mInterval;
}

bool TransformHistorian::isCompatible(const da::Entity &entity) const {
    return entity.hasAttribute<TransformHistory>() &&
           entity.hasAttribute<da::Transform>();
}

void TransformHistorian::updateEntity(const da::EntityPtr &entity) {
    mTime += getDelta();
    if (mTime >= mInterval) {
        mTime = sf::Time::Zero;
        
        da::Transform &xform = entity->getAttribute<da::Transform>();
        TransformHistory &prev = entity->getAttribute<TransformHistory>();
        
        prev.setPosition(xform.getPosition());
        prev.setRotation(xform.getRotation());
        prev.setScale(xform.getScale());
    }
}
