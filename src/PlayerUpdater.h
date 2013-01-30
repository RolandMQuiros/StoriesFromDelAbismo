#ifndef PLAYERUPDATER_H
#define PLAYERUPDATER_H

#include <SFML/Graphics/View.hpp>

#include "ColliderBehavior.h"
#include "Input.h"

class PlayerUpdater : public ColliderBehavior {
public:
    PlayerUpdater(sf::View &view, Input &input);
    const sf::View &getView() const;
private:
    sf::View &mView;
    Input &mInput;
    
    bool isCompatible(const da::Entity &entity) const;
    void updateEntity(const da::EntityPtr &entity);
    
    void onCollisionEnter(const da::EntityPtr &entity, const da::Entity &other);
    void onCollisionStay(const da::EntityPtr &entity, const da::Entity &other);
    void onCollisionExit(const da::EntityPtr &entity, const da::Entity &other);
};

#endif
