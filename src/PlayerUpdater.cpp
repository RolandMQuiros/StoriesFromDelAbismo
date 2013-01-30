#include <iostream>
#include <SFML/Window/Keyboard.hpp>
#include <da/Transform.h>

#include "Collider.h"
#include "Player.h"
#include "Velocities.h"

#include "Obstruction.h"

#include "PlayerUpdater.h"

PlayerUpdater::PlayerUpdater(sf::View &view, Input &input) :
mView(view),
mInput(input) {
    
}

const sf::View &PlayerUpdater::getView() const {
    return mView;
}

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
    int horz = mInput.isButtonHeld(Input::Right) -
               mInput.isButtonHeld(Input::Left);
    int vert = mInput.isButtonHeld(Input::Down) -
               mInput.isButtonHeld(Input::Up);
    
    // Mouse movement
    
    // Normalize cursor position
    sf::Vector2f distance;
    distance = (mInput.getAxes() * 2.f) - sf::Vector2f(1.f, 1.f);
    
    // Move view based on cursor
    mView.setCenter(xform.getPosition() + (distance * player.viewDistance));
    
    vels.speed.x = horz * player.walkSpeed;
    vels.speed.y = vert * player.walkSpeed;
    
    // The game states are simply a collection of Behavior settings.  For example, PLAYER_CONTROL state
    // allows the PlayerUpdater to handle player movement and camera control.  SCENE_RUN state gives that
    // control to the Director.
    // Lua Script -> Game -> Behaviors.  Where does Director fit into all this?  Merged into Game?
    
    //~ std::cout << "Cursor position: " << mInput.getCursorPosition().x << ", " << mInput.getCursorPosition().y << std::endl
              //~ << "Distance From Center: " << distance.x << ", " << distance.y << std::endl;
    
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