#include "TextCase.h"
#include <iostream>

TextCase::TextCase(float posX, float posY, int width, int height, int fontSize, int max) :
    m_title(nullptr),
    m_fontSize(fontSize),
    m_max(max),
    m_valid(nullptr),
    m_isUsing(false)
{
    //rectangle INIT
    m_case.x = posX;
    m_case.y = posY;
    m_case.width = width;
    m_case.height = height;
}

TextCase::~TextCase()
{
    delete m_valid;
    m_valid = nullptr;
}

void TextCase::event()
{
    //check if selected
    if (IsMouseButtonDown(0))
    {
        int x = GetMouseX();
        int y = GetMouseY();
        if (x > m_case.x && x < m_case.x + m_case.width && 
            y > m_case.y && y < m_case.y + m_case.height)
        {
            m_isUsing = true;
        }
        else
        {
            m_isUsing = false;
        }
    }

    //check writing
    if (m_isUsing)
    {
        char keyC = GetCharPressed();
        int key = GetKeyPressed();
        
        //delete with backspace
        if (IsKeyPressed(KEY_BACKSPACE) && !m_text.empty())
            m_text.pop_back(); 

        //check if the char is valid (if there are restrictions)
        if (m_valid)
        {
            if (!m_valid->count(keyC))
                return;
        }
        //write char
        if (keyC && m_text.size() < m_max)
            m_text += keyC;
    }    
}

void TextCase::render()
{
    //rectangle render
    if (m_isUsing)
        DrawRectangleLinesEx(m_case, 2, BLUE);
    else
        DrawRectangleLinesEx(m_case, 2, BLACK);

    //text render
    const char *sText = m_text.c_str();
    DrawText(sText, m_case.x+9, m_case.y+2, m_fontSize, BLACK);

    //title render
    if (m_title)
        DrawText(m_title, m_case.x+9, m_case.y-(m_fontSize-10), (m_fontSize-10), BLACK);
}

void TextCase::getText(char *text)
{
    strcpy(text, m_text.c_str());
}

void TextCase::setTitle(const char *title)
{
    m_title = title;
}

void TextCase::setValid(std::unordered_set<char> valid)
{
    m_valid = new std::unordered_set<char>(valid);
}
