#ifndef CAMERA_H
#define CAMERA_H

#include <set>

#include <SFML/Graphics/View.hpp>
#include <SFML/System/Time.hpp>

#include <da/Entity.h>
#include <da/Transform.h>

/**
 * Camera that follows entities, interpolating between changes and changing the
 * zoom to display all entities.
 */
class Camera {
public:
    enum Mode {
        Manual,
        Follow,
        FollowFit
    } mode;
    
    void addTarget(const da::EntityRef &target);
    void addTarget(const da::EntityPtr &target);
    void removeTarget(const da::EntityRef &target);
    void removeTarget(const da::EntityPtr &target);
    void clearTargets();
    
    sf::Vector2f getDestination() const;
    void setDestination(const sf::Vector2f &destination);
    
    const sf::View &getView() const;
    void update(const sf::Time &deltaTime);

private:
    sf::View mView;
    sf::Transform mEndTransform;
    sf::Vector2f mDestination;

    da::EntityGroup mTargets;
    
};

#endif
