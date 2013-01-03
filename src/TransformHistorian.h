#ifndef TRANSFORMHISTORIAN_H
#define TRANSFORMHISTORIAN_H

#include <SFML/System/Time.hpp>
#include <da/EntityBehavior.h>

class TransformHistorian : public da::EntityBehavior {
public:
    TransformHistorian();
    TransformHistorian(const sf::Time &interval);
    void setInterval(const sf::Time &interval);
    sf::Time getInterval() const;

private:
    sf::Time mInterval;
    sf::Time mTime;
    
    bool isCompatible(const da::Entity &entity) const;
    void updateEntity(const da::EntityPtr &entity);
};

#endif
