#ifndef MOTIONMOVER_H
#define MOTIONMOVER_H

#include <da/Behavior.h>
#include <Signals/Signal.h>

using namespace Gallant;

class MotionMover : public da::Behavior {
public:
    Signal1<const da::EntityRef &> emptyQueueHandler;

private:    
    bool isCompatible(const da::Entity &entity) const;
    
    void updateEntities(da::EntityGroup &entities);
    bool moveEntity(const da::EntityPtr &entity);
};

#endif
