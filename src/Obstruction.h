#ifndef OBSTRUCTION_H
#define OBSTRUCTION_H

#include <da/Attribute.h>

/**
 * Attribute of objects that are obstructions, like walls, platforms, etc.
 */
struct Obstruction : public da::Attribute<Obstruction> {
    enum Flags {
        Moving = 2,
        Thin = 4
    };
    
    char flags;
};

#endif
