#ifndef INPUT_H
#define INPUT_H

#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>

class Input {
public:
    enum Button {
        None = 0,
        Up = 1,
        Down = 2,
        Left = 3,
        Right = 4,
        Jump = 5,
        Shoot = 6,
        ButtonCount = 7
    };
    
    /**
     * Returns whether or not a button is pressed.  isButtonDown will only
     * return true for the single logic frame after the corresponding input is
     * triggered.  To check if the button is still pressed, use isButtonHeld.
     * @param $button
     *   The button to check
     * @return
     *   true if pressed, false otherwise
     */
    virtual bool isButtonDown(Button button) const = 0;
    /**
     * Returns whether a button is held down.
     * @param $button
     *   The button to check
     * @return
     *   true if held, false otherwise
     */
    virtual bool isButtonHeld(Button button) const = 0;
    /**
     * Returns whether or not a button is released.  isButtonUp will only return
     * true for the single logic frame after the corresponding input is
     * released.
     * @param $button
     *   The button to check
     * @return
     *   true if the button is released, false otherwise
     */
    virtual bool isButtonUp(Button button) const = 0;
    /**
     * Returns the location of the cursor.  Different input methods may have
     * different ways of specifying this.  For example, using a mouse, this
     * method might return the location of the hardware cursor relative to the
     * window.  Using a gamepad, it might correspond to the position of an
     * object in the game world, controlled by a thumbstick. Using a Guitar Hero
     * controller, it might be the position of the whammy bar(???).
     * @return
     *   The position of the cursor
     */
    virtual sf::Vector2f getCursorPosition() const = 0;
    virtual sf::Vector2f getAxes() const = 0;
    /**
     * Updates states that change with every logic frame, <em>before</em>
     * handling window events.
     */
    virtual void preUpdate() { }
    /**
     * Updates states that change with input events.
     * @param $event
     *   Input event to evaluate
     */
    virtual void handleEvent(const sf::Event &event) = 0;
    /**
     * Updates states that change with every logic frame, <em>after</em>
     * handling window events.
     */
    virtual void postUpdate() { }
};

#endif
