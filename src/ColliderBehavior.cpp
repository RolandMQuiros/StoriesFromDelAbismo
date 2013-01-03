#include "Collider.h"
#include "ColliderBehavior.h"

bool ColliderBehavior::isCompatible(const da::Entity &entity) const {
    return entity.hasAttribute<Collider>();
}

void ColliderBehavior::processCollisions(const da::EntityPtr &entity) {
    Collider &colls = entity->getAttribute<Collider>();
    
    for (unsigned int i = 0; i < colls.collisions.size(); i++) {
        Collision &collision = colls.collisions[i];
        if (collision.other.expired()) {
            continue;
        }
        da::Entity &other = *collision.other.lock();
        
        switch (collision.type) {
            case Collision::Enter:
                onCollisionEnter(entity, other);
                break;
            case Collision::Stay:
                onCollisionStay(entity, other);
                break;
            case Collision::Exit:
                onCollisionExit(entity, other);
                break;
        }
    }
}

void ColliderBehavior::onCollisionEnter(const da::EntityPtr &entity,
                                        const da::Entity &other) {

}

void ColliderBehavior::onCollisionStay(const da::EntityPtr &entity,
                                       const da::Entity &other) {

}

void ColliderBehavior::onCollisionExit(const da::EntityPtr &entity,
                                       const da::Entity &other) {
    
}
