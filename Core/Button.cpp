#include "Button.h"

Button::Button(float posX, float posY, int width, int height, const char* title, int fontSize) :
    m_title(title),
    m_fontSize(fontSize),
    m_down(false)
{
    //rectangle INIT
    m_case.x = posX;
    m_case.y = posY;
    m_case.width = width;
    m_case.height = height;
}

bool Button::pressed()
{
    //get values
    int x = GetMouseX();
    int y = GetMouseY();
    static bool inside = false;
    inside = (x > m_case.x && x < m_case.x + m_case.width 
                && y > m_case.y && y < m_case.y + m_case.height);

    //mouse pressed
    if (IsMouseButtonPressed(0))
    {
        m_down = inside;
    }

    //if mouse has been pressed but is no longer inside the button
    if (!inside)
        m_down = false;

    //mouse released
    if (IsMouseButtonReleased(0) && m_down)
    {
        m_down = false;

        return inside;
    }

    return false;
}

void Button::render()
{
    //rectangle render
    if (m_down)
        DrawRectangleLinesEx(m_case, 2, BLUE);
    else
        DrawRectangleLinesEx(m_case, 2, BLACK);

    //title render
    int textWidth = MeasureText(m_title, m_fontSize);
    DrawText(m_title, m_case.x+(m_case.width/2)-(textWidth/2), m_case.y+(m_case.height/2)-(m_fontSize/2), m_fontSize, BLACK);
}