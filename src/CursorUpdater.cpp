#include <SFML/Window/Mouse.hpp>

#include <da/Transform.h>
#include "Cursor.h"

bool CursorUpdater::isCompatible(const da::Entity &entity) const {
    return entity.hasAttribute<Cursor>() &&
           entity.hasAttribute<da::Transform>();
}

void CursorUpdater::updateEntity(const da::EntityPtr &entity) {
    da::Transform &xform = entity->getAttribute<da::Transform>();
    
    
}
