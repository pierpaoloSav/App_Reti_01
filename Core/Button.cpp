#include "Button.h"

#include <iostream>

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
    if (IsMouseButtonDown(0))
    {
        int x = GetMouseX();
        int y = GetMouseY();
        if (x > m_case.x && x < m_case.x + m_case.width && 
            y > m_case.y && y < m_case.y + m_case.height)
        {
            m_down = true;
        }
        else
        {
            m_down = false;
        }
    }
    
    if (m_down && IsMouseButtonUp(0))
    {
        m_down = false;
        return true;
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