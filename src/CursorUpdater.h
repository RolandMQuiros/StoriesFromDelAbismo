#ifndef CURSORUPDATER_H
#define CURSORUPDATER_H

#include <da/EntityBehavior.h>

class CursorUpdater : public da::EntityBehavior {
    sf::Vector2f mMousePos;
    bool isCompatible(const da::Entity &entity) const;
    void beginUpdate(da::EntityGroup &entities);
    void updateEntity(const da::EntityPtr &entity);
};

#endif
