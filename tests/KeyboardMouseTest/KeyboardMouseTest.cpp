#include <set>
#include <sstream>
#include <string>

#include <gtest/gtest.h>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <KeyboardMouseInput.h>

// Shared window for all tests
sf::RenderWindow window(sf::VideoMode(640, 480), "Keyboard/Mouse Input Test");

// Input fixture
class InputFixture : public ::testing::Test {
public:
    KeyboardMouseInput input;
    InputFixture();
};

InputFixture::InputFixture() :
input(window) {
    input.assignKey(sf::Keyboard::W, Input::Up);
    input.assignKey(sf::Keyboard::A, Input::Left);
    input.assignKey(sf::Keyboard::S, Input::Down);
    input.assignKey(sf::Keyboard::D, Input::Right);
    input.assignMouseButton(sf::Mouse::Left, Input::Shoot);
}

TEST_F(InputFixture, PressReleaseTest) {
    sf::Text description;
    description.setCharacterSize(12);
    description.setString("Here, we're testing if the KeyboardMouseInput class "
        "correctly identifies key press/release events.\nTo complete the test, "
        "press the buttons listed.  They'll be verified when the button is "
        "released.");
    
    sf::Text debugText;
    debugText.setCharacterSize(16);
    debugText.setPosition(36.f, 36.f);
    
    std::set<std::string> remaining { "W", "A", "S", "D", "Mouse1" };
    
    bool running = true;
    
    while (running) {
        sf::Event event;
        while (window.pollEvent(event)) {
            input.handleEvent(event);
            
            // Make sure the KeyboardMouseInput is correctly identifying press
            // events
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::W:
                        EXPECT_EQ(input.isButtonDown(Input::Up), true);
                        break;
                    case sf::Keyboard::A:
                        EXPECT_EQ(input.isButtonDown(Input::Left), true);
                        break;
                    case sf::Keyboard::S:
                        EXPECT_EQ(input.isButtonDown(Input::Down), true);
                        break;
                    case sf::Keyboard::D:
                        EXPECT_EQ(input.isButtonDown(Input::Right), true);
                        break;
                    case sf::Keyboard::Escape:
                        running = false;
                        FAIL() << "Skipped test";
                        break;
                }
            } else if (event.type == sf::Event::KeyReleased) {
                switch (event.key.code) {
                    case sf::Keyboard::W:
                        EXPECT_EQ(input.isButtonUp(Input::Up), true);
                        remaining.erase("W");
                        break;
                    case sf::Keyboard::A:
                        EXPECT_EQ(input.isButtonUp(Input::Left), true);
                        remaining.erase("A");
                        break;
                    case sf::Keyboard::S:
                        EXPECT_EQ(input.isButtonUp(Input::Down), true);
                        remaining.erase("S");
                        break;
                    case sf::Keyboard::D:
                        EXPECT_EQ(input.isButtonUp(Input::Right), true);
                        remaining.erase("D");
                        break;
                }
            } else if (event.type == sf::Event::MouseButtonPressed &&
                       event.mouseButton.button == sf::Mouse::Left) {
                EXPECT_EQ(input.isButtonDown(Input::Shoot), true);
            } else if (event.type == sf::Event::MouseButtonReleased &&
                       event.mouseButton.button == sf::Mouse::Left) {
                EXPECT_EQ(input.isButtonUp(Input::Shoot), true);
                remaining.erase("Mouse1");
            }
        }
        
        if (remaining.empty()) {
            running = false;
            SUCCEED();
        } else {
            std::stringstream ss;
            for (std::set<std::string>::iterator iter = remaining.begin();
                 iter != remaining.end(); iter++) {
                ss << ' ' << *iter;
            }
            
            debugText.setString(ss.str());
        }
        
        window.clear();
        window.draw(description);
        window.draw(debugText);
        window.display();
    }
}

TEST_F(InputFixture, MousePositionTest) {
    // Description text
    sf::Text description;
    description.setCharacterSize(12);
    description.setString("This test checks if KeyboardMouseInput correctly "
        "calculates the mouse coordinates.\nClick on the four red boxes below "
        "to complete the test, or press Escape to exit (forces a failure).\n\n"
        "You'll have to do this twice: once for locked mouse input, and once "
        "for unlocked.\nLocked constrains the mouse to the window, while "
        "unlocked doesn't.");
    
    sf::Text currentTest;
    currentTest.setCharacterSize(12);
    currentTest.setString("Currently testing locked mode");
    currentTest.setPosition(0.f, 80.f);
    
    // Mouse coordinate display
    sf::Text mouseCoords;
    mouseCoords.setCharacterSize(12);
    mouseCoords.setPosition(0.f, 468.f);
    
    // Cursor display polygon
    sf::ConvexShape cursor(3);
    cursor.setPoint(0, sf::Vector2f(0.f, 0.f));
    cursor.setPoint(1, sf::Vector2f(0.f, 8.f));
    cursor.setPoint(2, sf::Vector2f(4.f, 6.f));
    cursor.setFillColor(sf::Color::White);
    
    // Boxes to click
    sf::IntRect topLeft(100, 100, 16, 16);
    sf::IntRect topRight(540, 100, 16, 16);
    sf::IntRect bottomLeft(100, 380, 16, 16);
    sf::IntRect bottomRight(540, 380, 16, 16);
    
    // Box display polygon
    sf::RectangleShape shape(sf::Vector2f(16.f, 16.f));
    shape.setFillColor(sf::Color::Red);
    
    // Squares left to draw
    std::set<sf::IntRect*> remaining {
        &topLeft, &topRight, &bottomLeft, &bottomRight
    };
    
    // Hide OS cursor
    window.setMouseCursorVisible(false);
    
    // Lock mouse to screen
    input.setMouseLock(true);
    bool locked = true;
    
    // Focus switches
    bool focused = true;
    
    bool running = true;
    
    while (running) {
        input.preUpdate();
        sf::Event event;
        while (window.pollEvent(event)) {
            input.handleEvent(event);
            
            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Escape) {
                running = false;
                FAIL() << "Skipped test";
            } else if (event.type == sf::Event::LostFocus) {
                focused = false;
            } else if (event.type == sf::Event::GainedFocus) {
                focused = true;
            }
        }
        
        if (!focused) {
            continue;
        }
        
        input.postUpdate();
        
        // Check box intersections
        sf::Vector2i cursorPos(input.getCursorPosition().x,
                               input.getCursorPosition().y);
        
        if (topLeft.contains(cursorPos) && input.isButtonDown(Input::Shoot)) {
            remaining.erase(&topLeft);
        }
        
        if (topRight.contains(cursorPos) && input.isButtonDown(Input::Shoot)) {
            remaining.erase(&topRight);
        }
        
        if (bottomLeft.contains(cursorPos) && input.isButtonDown(Input::Shoot)) {
            remaining.erase(&bottomLeft);
        }
        
        if (bottomRight.contains(cursorPos) && input.isButtonDown(Input::Shoot)) {
            remaining.erase(&bottomRight);
        }
        
        cursor.setPosition(input.getCursorPosition());
        
        // Exit once all boxes are clicked
        if (remaining.empty()) {
            // Repeat the tests, but using an unlocked cursor.
            if (locked) {
                locked = false;
                input.setMouseLock(false);
                remaining.insert(&topLeft);
                remaining.insert(&topRight);
                remaining.insert(&bottomLeft);
                remaining.insert(&bottomRight);
                currentTest.setString("Currently testing unlocked mode");
            } else {
                running = false;
                SUCCEED();
            }
        }
        
        std::stringstream ss;
        ss << "Mouse (" << input.getCursorPosition().x << ", "
           << input.getCursorPosition().y << ')';
        mouseCoords.setString(ss.str());
        
        window.clear();
        // Draw the remaining boxes
        std::set<sf::IntRect*>::iterator iter;
        for (iter = remaining.begin(); iter != remaining.end(); iter++) {
            shape.setPosition((*iter)->left, (*iter)->top);
            window.draw(shape);
        }
        window.draw(description);
        window.draw(currentTest);
        window.draw(mouseCoords);
        window.draw(cursor);
        window.display();
    };
}

