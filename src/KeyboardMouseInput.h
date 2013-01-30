#ifndef KEYBOARDMOUSEINPUT_H
#define KEYBOARDMOUSEINPUT_H

#include <vector>
#include <SFML/Window/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include "Input.h"

class KeyboardMouseInput : public Input {
public:
    KeyboardMouseInput(sf::Window &window);
    bool isButtonDown(Input::Button button) const;
    bool isButtonHeld(Input::Button button) const;
    bool isButtonUp  (Input::Button button) const;
    sf::Vector2f getCursorPosition() const;
    sf::Vector2f getAxes() const;
    void preUpdate();
    void handleEvent(const sf::Event &event);
    void postUpdate();

    void assignKey(sf::Keyboard::Key key, Input::Button button);
    void assignMouseButton(sf::Mouse::Button mouseBtn, Input::Button button);
    void setMouseLock(bool lock);

private:
    enum ButtonState {
        None,
        Down,
        Held,
        Up
    };
    
    sf::Window   &mWindow;
    sf::Vector2i mScreenCenter;
    sf::Vector2f mCursor;
    
    std::vector<ButtonState>   mButtonStates;
    std::vector<Input::Button> mKeyMap;
    
    bool mIsMouseLocked;
    
    void updateKeys();
    bool handleKeyEvent(const sf::Event &event);
    
    void updateMouse();
    bool handleMouseEvent(const sf::Event &event);
    
};

#endif
