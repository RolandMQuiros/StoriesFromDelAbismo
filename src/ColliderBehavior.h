#ifndef COLLIDERBEHAVIOR_H
#define COLLIDERBEHAVIOR_H

#include <da/EntityBehavior.h>

class ColliderBehavior : public da::EntityBehavior {
protected:
    virtual bool isCompatible(const da::Entity &entity) const;
    
    void processCollisions(const da::EntityPtr &entity);
    
    virtual void onCollisionEnter(const da::EntityPtr &entity,
                                  const da::Entity &other);

    virtual void onCollisionStay(const da::EntityPtr &entity,
                                 const da::Entity &other);

    virtual void onCollisionExit(const da::EntityPtr &entity,
                                 const da::Entity &other);
};

#endif
