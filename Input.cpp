#include "Input.h"

Input::Input() : m_mouseX(0), m_mouseY(0), m_mouseRelX(0), m_mouseRelY(0), m_terminate(false)
{
    for(int i(0); i<SDL_NUM_SCANCODES; i++)
        m_keys[i] = false;

    for(int i(0); i<8; i++)
        m_mouseButtons[i] = false;
}

Input::~Input()
{
}

void Input::updateEvents()
{
    m_mouseRelX = 0;
    m_mouseRelY = 0;

    while(SDL_PollEvent(&m_events))
    {
        switch(m_events.type)
        {
        case SDL_KEYDOWN:
            m_keys[m_events.key.keysym.scancode] = true;
            break;

        case SDL_KEYUP:
            m_keys[m_events.key.keysym.scancode] = false;
            break;

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
