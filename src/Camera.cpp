#include <algorithm>
#include "Camera.h"

void Camera::addTarget(const da::EntityRef &target) {
    if (!target.expired() && target.lock()->hasAttribute<da::Transform>()) {
        mTargets.insert(target);
    }
}

void Camera::addTarget(const da::EntityPtr &target) {
    addTarget(da::EntityRef(target));
}

void Camera::removeTarget(const da::EntityRef &target) {
    if (!target.expired()) {
        da::EntityGroup::iterator iter = mTargets.find(target);
        
        if (iter != mTargets.end()) {
            mTargets.erase(iter);
        }
    }
}

void Camera::removeTarget(const da::EntityPtr &target) {
    if (target) {
        removeTarget(da::EntityRef(target));
    }
}

sf::Vector2f Camera::getDestination() const {
    return mDestination;
}

void Camera::setDestination(const sf::Vector2f &destination) {
    mDestination = destination;
}

const sf::View &Camera::getView() const {
    return mView;
}

void Camera::update(const sf::Time &deltaTime) {
    if (mode != Manual && !mTargets.empty()) {
        // Calculate centroid
        sf::Vector2f centroid;
        float left, top, right, bottom;
        
        da::EntityGroup::iterator iter;
        for (iter = mTargets.begin(); iter != mTargets.end(); iter++) {
            da::Transform &xform = iter->lock()->getAttribute<da::Transform>();
            centroid += xform.getPosition();
            
            if (mode == FollowFit) {
                left   = std::min(xform.getPosition().x, left);
                top    = std::min(xform.getPosition().y, top);
                right  = std::max(xform.getPosition().x, right);
                bottom = std::max(xform.getPosition().y, bottom);
            }
        }
        centroid.x /= mTargets.size();
        centroid.y /= mTargets.size();
        mDestination = centroid;
        
        
    }
    
    // Center camera on destination
    sf::Vector2f dp = mDestination - mView.getCenter();
    mView.move(dp * deltaTime.asSeconds());
}
