#include <algorithm>
#include "KeyboardMouseInput.h"

// Sarajevo Dusk

KeyboardMouseInput::KeyboardMouseInput(sf::Window &window) :
mWindow(window),
mScreenCenter(window.getSize().x / 2, window.getSize().y / 2),
mButtonStates(Input::ButtonCount),
mKeyMap(sf::Keyboard::KeyCount + sf::Mouse::ButtonCount) {
    // Disable key event repeating
    mWindow.setKeyRepeatEnabled(false);
}

bool KeyboardMouseInput::isButtonDown(Button button) const {
    return mButtonStates[button] == Down;
}

bool KeyboardMouseInput::isButtonHeld(Button button) const {
    return mButtonStates[button] == Held;
}

bool KeyboardMouseInput::isButtonUp(Button button) const {
    return mButtonStates[button] == Up;
}

sf::Vector2f KeyboardMouseInput::getCursorPosition() const {
    return mCursor;
}

void KeyboardMouseInput::preUpdate() {
    // If a button was pushed in the previous frame, then it is held in the
    // current one.
    for (unsigned int i = 0; i < Input::ButtonCount; i++) {
        switch (mButtonStates[i]) {
            case Down:
                mButtonStates[i] = Held;
                break;
            case Up:
                mButtonStates[i] = None;
                break;
        }
    }
}

void KeyboardMouseInput::handleEvent(const sf::Event &event) {
    sf::Keyboard::Key key;
    sf::Mouse::Button mouseBtn;
    Input::Button     button;
    sf::Vector2f      mickey;
    
    switch (event.type) {
        // Handle window resizes
        case sf::Event::Resized:
            mScreenCenter.x = event.size.width  / 2;
            mScreenCenter.y = event.size.height / 2;
            break;
        // Handle key presses
        case sf::Event::KeyPressed:
            key    = event.key.code;
            button = mKeyMap[key];
            if (button != Input::None) {
                mButtonStates[button] = Down;
            }
            break;
        // Handle key release
        case sf::Event::KeyReleased:
            key    = event.key.code;
            button = mKeyMap[key];
            if (button != Input::None) {
                mButtonStates[button] = Up;
            }
            break;
        // Handle mouse movement (unclocked)
        case sf::Event::MouseMoved:
            if (!mIsMouseLocked) {
                mCursor.x = event.mouseMove.x;
                mCursor.y = event.mouseMove.y;
            }
            break;
        // Handle mouse button press
        case sf::Event::MouseButtonPressed:
            mouseBtn = event.mouseButton.button;
            button   = mKeyMap[sf::Keyboard::KeyCount + mouseBtn];
            if (button != Input::None) {
                mButtonStates[button] = Down;
            }
            break;
        // Handle mouse button release
        case sf::Event::MouseButtonReleased:
            mouseBtn = event.mouseButton.button;
            button   = mKeyMap[sf::Keyboard::KeyCount + mouseBtn];
            if (button != Input::None) {
                mButtonStates[button] = Up;
            }
            break;
    }
}

void KeyboardMouseInput::postUpdate() {
    // "Raw" mouse movement, when mouse is constrained to the screen
    if (mIsMouseLocked) {
        sf::Vector2i mickey = sf::Mouse::getPosition() - (mWindow.getPosition()
                                                          + mScreenCenter);
        mCursor.x += mickey.x;
        mCursor.y += mickey.y;
        
        sf::Vector2i winBounds;
        mCursor.x = std::min(std::max(mCursor.x, 0.f),
                             (float)mWindow.getSize().x);
        mCursor.y = std::min(std::max(mCursor.y, 0.f),
                             (float)mWindow.getSize().y);
        
        sf::Mouse::setPosition(mWindow.getPosition() + mScreenCenter);
    }
}

void KeyboardMouseInput::assignKey(sf::Keyboard::Key key,
                                   Input::Button button) {
    mKeyMap[(int)key] = button;
}

void KeyboardMouseInput::assignMouseButton(sf::Mouse::Button mouseBtn,
                                           Input::Button button) {
    mKeyMap[sf::Keyboard::KeyCount + (int)mouseBtn] = button;
}

void KeyboardMouseInput::setMouseLock(bool locked) {
    mIsMouseLocked = locked;
}
