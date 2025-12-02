#include "Checkbox.h"

Checkbox::Checkbox(float posX, float posY, int side) :
    m_status(false),
    m_down(false)
{
    //rectangle INIT
    m_case.x = posX;
    m_case.y = posY;
    m_case.width = side;
    m_case.height = side;
}

void Checkbox::event()
{
    //get values
    int x = GetMouseX();
    int y = GetMouseY();
    static bool inside = false;
    inside = (x > m_case.x && x < m_case.x + m_case.width 
                && y > m_case.y && y < m_case.y + m_case.height);

    //mouse pressed
    if (IsMouseButtonPressed(0))
        m_down = inside;

    //if mouse has been pressed but is no longer inside the button
    if (!inside)
        m_down = false;

    //mouse released
    if (IsMouseButtonReleased(0) && m_down)
    {
        m_down = false;

        m_status = !m_status;
    }
}

bool Checkbox::getStatus()
{
    return m_status;
}

void Checkbox::render()
{
    //rectangle render
    if (m_status)
        DrawRectangleRec(m_case, BLUE);
    else
        DrawRectangleLinesEx(m_case, 2, BLACK);
}