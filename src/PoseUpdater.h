#ifndef POSEUPDATER_H
#define POSEUPDATER_H

#include <da/EntityBehavior.h>
#include <Signals/Signal.h>

using namespace Gallant;

class PoseUpdater : public da::EntityBehavior {
public:
    Signal1<const da::EntityRef &> finished;
private:    
    bool isCompatible(const da::Entity &entity) const;
    void updateEntity(const da::EntityPtr &entity);
};

#endif
