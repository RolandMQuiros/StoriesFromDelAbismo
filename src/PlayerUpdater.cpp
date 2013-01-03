#include <SFML/Window/Keyboard.hpp>
#include <da/Transform.h>

#include "Collider.h"
#include "Player.h"
#include "Velocities.h"

#include "Obstruction.h"

#include "PlayerUpdater.h"

bool PlayerUpdater::isCompatible(const da::Entity &entity) const {
    return entity.hasAttribute<Player>() &&
           entity.hasAttribute<Collider>() &&
           entity.hasAttribute<Velocities>() &&
           entity.hasAttribute<da::Transform>();
}

void PlayerUpdater::updateEntity(const da::EntityPtr &entity) {
    Player        &player = entity->getAttribute<Player>();
    Collider      &coll   = entity->getAttribute<Collider>();
    Velocities    &vels   = entity->getAttribute<Velocities>();
    da::Transform &xform  = entity->getAttribute<da::Transform>();
    
    // Keyboard movement
    int horz = sf::Keyboard::isKeyPressed(sf::Keyboard::D) -
               sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    int vert = sf::Keyboard::isKeyPressed(sf::Keyboard::S) -
               sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    
    vels.speed.x = horz * player.walkSpeed;
    vels.speed.y = vert * player.walkSpeed;
    
    processCollisions(entity);
}

void PlayerUpdater::onCollisionEnter(const da::EntityPtr &entity,
                                     const da::Entity &other) {
}

void PlayerUpdater::onCollisionStay(const da::EntityPtr &entity,
                                    const da::Entity &other) {
    
}

void PlayerUpdater::onCollisionExit(const da::EntityPtr &entity,
                                    const da::Entity &other) {
    
}