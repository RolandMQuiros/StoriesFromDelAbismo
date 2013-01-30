#ifndef PLAYER_H
#define PLAYER_H

#include <da/Attribute.h>

struct Player : public da::Attribute<Player> {
    float walkSpeed;
    float direction;
    float viewDistance;
};

#endif
