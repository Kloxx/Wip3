#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

// SDL2
#include <SDL2/SDL.h>

class Input
{
public:
    Input();
    ~Input();
    void updateEvents();
    bool terminate() const;
    bool getKey(const SDL_Scancode key) const;
    bool getMouseButton(const Uint8 button) const;
    bool mouseMotion() const;
    int getMouseX() const;
    int getMouseY() const;
    int getMouseRelX() const;
    int getMouseRelY() const;
    void afficherPtr(bool response) const;
    void capturePtr(bool response) const;
    void openJoysticks();

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
