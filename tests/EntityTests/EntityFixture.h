#ifndef ENTITYFIXTURE_H
#define ENTITYFIXTURE_H

#include <functional>
#include <string>

#include <gtest/gtest.h>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <da/ContentManager.h>
#include <da/EntityManager.h>
#include <da/SpatialRenderer.h>

#include <KeyboardMouseInput.h>

class EntityFixture;
void emptyCallback(EntityFixture &fixture, const sf::Time &time);
void emptyHandler(EntityFixture &fixture, const sf::Event &event);
void emptyDraw(EntityFixture &fixure);

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
    sf::View &GetView();
    da::ContentManager &GetContent();
    da::EntityManager &GetManager();
    da::SpatialRenderer &GetRenderer();
    KeyboardMouseInput &GetInput();
    
    void Run(
        std::function<void (EntityFixture &, const sf::Time &)> callback = emptyCallback,
        std::function<void (EntityFixture &, const sf::Event &)> handler = emptyHandler,
        std::function<void (EntityFixture &)> draw = emptyDraw
    );
private:
    sf::RenderWindow mWindow;
    sf::View mView;
    da::ContentManager mContent;
    da::EntityManager mManager;
    KeyboardMouseInput mInput;
    std::shared_ptr<da::SpatialRenderer> mRenderer;
};

#endif
