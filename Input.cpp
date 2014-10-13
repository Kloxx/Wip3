#include "Input.h"

Input::Input() :
    m_mouseX(0), m_mouseY(0), m_mouseRelX(0), m_mouseRelY(0),
    m_numJoysticks(SDL_NumJoysticks()),
    m_terminate(false)
{
    // Keyboard & mouse
    for(int i(0); i<SDL_NUM_SCANCODES; i++)
        m_keys[i] = false;

    for(int i(0); i<8; i++)
        m_mouseButtons[i] = false;

    // Joysticks
    if(m_numJoysticks > 4)
        m_numJoysticks = 4; // Sets maximum joysticks to 4

    for(int i(0); i<4; i++)
    {
        for(int j(0); j<13; j++)
            m_joystickButtons[i][j] = false;
        for(int j(0); j<6; j++)
            m_joystickAxes[i][j] = 0;
        m_joystickHat[i] = SDL_HAT_CENTERED;
    }
}

Input::~Input()
{
    for(int i(0); i<m_numJoysticks; i++)
        SDL_JoystickClose(m_joysticks[i]); // Close Joysticks
    /*
    /!\ There might be an error if a device is removed during game session /!\
     TODO : - change m_numJoysticks and close joysticks if SDL_JOYDEVICEREMOVED in events
            - re-open m_joysticks
    */
}

void Input::openJoysticks()
{
    for(int i(0); i<m_numJoysticks; i++)
        m_joysticks[i] = SDL_JoystickOpen(i); // Open Joysticks
}

void Input::updateEvents()
{
    m_mouseRelX = 0;
    m_mouseRelY = 0;

    while(SDL_PollEvent(&m_events))
    {
        switch(m_events.type)
        {
        // Keyboard events
        case SDL_KEYDOWN:
            m_keys[m_events.key.keysym.scancode] = true;
            break;

        case SDL_KEYUP:
            m_keys[m_events.key.keysym.scancode] = false;
            break;

        // Mouse events
        case SDL_MOUSEBUTTONDOWN:
            m_mouseButtons[m_events.button.button] = true;
            break;

        case SDL_MOUSEBUTTONUP:
            m_mouseButtons[m_events.button.button] = false;
            break;

        case SDL_MOUSEMOTION:
            m_mouseX = m_events.motion.x;
            m_mouseY = m_events.motion.y;

            m_mouseRelX = m_events.motion.xrel;
            m_mouseRelY = m_events.motion.yrel;
            break;

        // Joystick events
        case SDL_JOYBUTTONDOWN:
            m_joystickButtons[m_events.jbutton.which][m_events.jbutton.button] = true;
            break;

        case SDL_JOYBUTTONUP:
            m_joystickButtons[m_events.jbutton.which][m_events.jbutton.button] = false;
            break;

        case SDL_JOYAXISMOTION:
            m_joystickAxes[m_events.jaxis.which][m_events.jaxis.axis] = m_events.jaxis.value;
            break;

        case SDL_JOYHATMOTION:
            m_joystickHat[m_events.jhat.which] = m_events.jhat.value;

        // Window events
        case SDL_WINDOWEVENT:
            if(m_events.window.event == SDL_WINDOWEVENT_CLOSE)
                m_terminate = true;
            break;

        default:
            break;
        }
    }
}

bool Input::terminate() const
{
    return m_terminate;
}

bool Input::getKey(const SDL_Scancode key) const
{
    return m_keys[key];
}

bool Input::getMouseButton(const Uint8 button) const
{
    return m_mouseButtons[button];
}

bool Input::mouseMotion() const
{
    return m_mouseRelX || m_mouseRelY;
}

int Input::getMouseX() const
{
    return m_mouseX;
}

int Input::getMouseY() const
{
    return m_mouseY;
}

int Input::getMouseRelX() const
{
    return m_mouseRelX;
}

int Input::getMouseRelY() const
{
    return m_mouseRelY;
}

bool Input::getJoystickButton(const int joystickNumber, const Uint8 button) const
{
    return m_joystickButtons[joystickNumber][button];
}

Sint16 Input::getJoystickAxes(const int joystickNumber, const Uint8 axis) const
{
    return m_joystickAxes[joystickNumber][axis];
}

Uint8 Input::getJoystickHat(const int joystickNumber) const
{
    return m_joystickHat[joystickNumber];
}

void Input::afficherPtr(bool response) const
{
    if(response)
        SDL_ShowCursor(SDL_ENABLE);
    else
        SDL_ShowCursor(SDL_DISABLE);
}

void Input::capturePtr(bool response) const
{
    if(response)
        SDL_SetRelativeMouseMode(SDL_TRUE);
    else
        SDL_SetRelativeMouseMode(SDL_FALSE);
}
