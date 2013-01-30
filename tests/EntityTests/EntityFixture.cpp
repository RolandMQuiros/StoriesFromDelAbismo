#include <sstream>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include "EntityFixture.h"

void emptyCallback(EntityFixture &fixture, const sf::Time &time) { }
void emptyHandler(EntityFixture &fixture, const sf::Event &event) { }
void emptyDraw(EntityFixture &fixture) { }

EntityFixture::EntityFixture() :
mWindow(sf::VideoMode(640, 480), "Entity Testing Fixture", sf::Style::Close),
mView(sf::FloatRect(0.f, 0.f, 320.f, 240.f)),
mRenderer(new da::SpatialRenderer(mWindow)),
mInput(mWindow) {
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

sf::View &EntityFixture::GetView() {
    return mView;
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

KeyboardMouseInput &EntityFixture::GetInput() {
    return mInput;
}

void EntityFixture::Run(std::function<void (EntityFixture &, const sf::Time &)> callback,
        std::function<void (EntityFixture &, const sf::Event &)> handler,
        std::function<void (EntityFixture &)> draw) {
    sf::Clock frameClock;
    sf::Time frameTime;
    
    sf::Time secTime;
    sf::Text fpsText;
    fpsText.setCharacterSize(10);
    
    try {
        while (mWindow.isOpen()) {
            // Check for exit events
            sf::Event event;
            
            mInput.preUpdate();
            while (mWindow.pollEvent(event)) {
                mInput.handleEvent(event);
                
                if (event.type == sf::Event::Closed) {
                    mWindow.close();
                }
                
                handler(*this, event);
            }
            mInput.postUpdate();
            
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
            mWindow.setView(mView);
            
            // Call the provided custom loop function
            callback(*this, frameTime);
            
            // Update Spatial Renderer
            mRenderer->update(frameTime);
            draw(*this);
            
            mWindow.setView(mWindow.getDefaultView());
            mWindow.draw(fpsText);
            
            mWindow.display();
        }
    } catch (da::DAException &e) {
        da::DAException except(__EXCEPTSRC__, "");
        except.pushMessage(e);
        throw except;
    }
}
