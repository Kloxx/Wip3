#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

// SDL2
#include <SDL2/SDL.h>
#include <iostream>

class Input
{
public:
    Input();
    ~Input();
    void updateEvents();
    bool terminate() const;

    // Keyboard & mouse
    bool getKey(const SDL_Scancode key) const;
    bool getMouseButton(const Uint8 button) const;
    bool mouseMotion() const;
    int getMouseX() const;
    int getMouseY() const;
    int getMouseRelX() const;
    int getMouseRelY() const;

    // Joysticks
    void openJoysticks();
    void closeJoysticks();
    bool getJoystickButton(const int joystickNumber, const Uint8 button) const;
    int getJoystickAxes(const int joystickNumber, const Uint8 axis) const;
    Uint8 getJoystickHat(const int joystickNumber) const;

    // Pointer
    void afficherPtr(bool response) const;
    void capturePtr(bool response) const;

private:
    SDL_Event m_events;

    // Keyboard & mouse
    bool m_keys[SDL_NUM_SCANCODES];
    bool m_mouseButtons[8];

    int m_mouseX;
    int m_mouseY;
    int m_mouseRelX;
    int m_mouseRelY;

    // Joysticks
    int m_numJoysticks;
    SDL_Joystick* m_joysticks[4];

    bool m_joystickButtons[4][13];  // Max 13 buttons
    Sint16 m_joystickAxes[4][6];    // Max 6 axes
    Uint8 m_joystickHat[4];

    // Close
    bool m_terminate;
};



#endif // INPUT_H_INCLUDED
