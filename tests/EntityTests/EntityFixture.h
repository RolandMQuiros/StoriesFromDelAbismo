#ifndef ENTITYFIXTURE_H
#define ENTITYFIXTURE_H

#include <functional>
#include <string>

#include <gtest/gtest.h>
#include <SFML/Graphics/RenderWindow.hpp>

#include <da/ContentManager.h>
#include <da/EntityManager.h>
#include <da/SpatialRenderer.h>

void emptyCallback(const sf::Time &time);

/**
 * Testing fixture for Entity Attributes and Systems.
 */
class EntityFixture : public ::testing::Test {
public:    
    EntityFixture();
    ~EntityFixture();
    
    void SetUp();
    void TearDown();
    
    void ResetDisplay(sf::VideoMode mode, const std::string &title);
    
    sf::RenderWindow &GetWindow();
    da::ContentManager &GetContent();
    da::EntityManager &GetManager();
    da::SpatialRenderer &GetRenderer();
    
    void Run(std::function<void(const sf::Time &)> callback = emptyCallback);
private:
    sf::RenderWindow mWindow;
    da::ContentManager mContent;
    da::EntityManager mManager;
    std::shared_ptr<da::SpatialRenderer> mRenderer;
    
};

#endif
