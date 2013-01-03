#include <sstream>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include "EntityFixture.h"

void emptyCallback(const sf::Time &time) { }

EntityFixture::EntityFixture() :
mWindow(sf::VideoMode(640, 480), "Entity Testing Fixture", sf::Style::Close),
mRenderer(new da::SpatialRenderer(mWindow)) {
    mManager.addBehavior(mRenderer);
}

EntityFixture::~EntityFixture() {
    
}

void EntityFixture::SetUp() {
    
}

void EntityFixture::TearDown() {
    
}

sf::RenderWindow &EntityFixture::GetWindow() {
    return mWindow;
}

da::ContentManager &EntityFixture::GetContent() {
    return mContent;
}

da::EntityManager &EntityFixture::GetManager() {
    return mManager;
}

da::SpatialRenderer &EntityFixture::GetRenderer() {
    return *mRenderer;
}

void EntityFixture::Run(std::function<void (const sf::Time &)> callback) {
    sf::Clock frameClock;
    sf::Time frameTime;
    
    sf::Time secTime;
    sf::Text fpsText;
    fpsText.setCharacterSize(10);
    
    try {
        while (mWindow.isOpen()) {
            // Check for exit events
            sf::Event event;
            while (mWindow.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    mWindow.close();
                }
            }
            
            // Update delta time
            frameTime = frameClock.restart();
            
            secTime += frameTime;
            if (secTime > sf::seconds(1.f)) {
                secTime = sf::Time::Zero;
                std::stringstream ss;
                ss << "FPS: " << (1.f / frameTime.asSeconds());
                fpsText.setString(ss.str());
            }
            
            mWindow.clear();
            
            // Call the provided custom loop function
            callback(frameTime);
            
            // Update Spatial Renderer
            mRenderer->update(frameTime);
            
            mWindow.draw(fpsText);
            
            mWindow.display();
        }
    } catch (da::DAException &e) {
        da::DAException except(__EXCEPTSRC__, "");
        except.pushMessage(e);
        throw except;
    }
}
