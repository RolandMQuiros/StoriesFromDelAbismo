#ifndef ACTOR_H
#define ACTOR_H

#include <string>
#include <da/Attribute.h>
#include <Signals/Signal.h>

using namespace Gallant;

struct Actor : public da::Attribute<Actor> {
    std::string name;
};

#endif
