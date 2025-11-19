#include "TextCase.h"

TextCase::TextCase(float posX, float posY, int width, int height, int max) :
    m_title(nullptr),
    m_fontSize(height),
    m_max(max),
    m_valid(nullptr),

    m_isUsing(false),
    m_down(false)
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
        if (IsMouseButtonReleased(0))
        {
            m_isUsing = inside*m_down;
            m_down = false;
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
    if (m_isUsing || m_down)
        DrawRectangleLinesEx(m_case, 2, BLUE);
    else
        DrawRectangleLinesEx(m_case, 2, BLACK);

    //text render
    static int xMargin = m_case.width/30;
    static int yMargin = m_fontSize/30 * 2;
    const char *sText = m_text.c_str();
    DrawText(sText, m_case.x+xMargin, m_case.y+yMargin, m_fontSize, BLACK);

    //title render
    static int titleSize = m_fontSize - (m_fontSize/3);
    if (m_title)
        DrawText(m_title, m_case.x+xMargin, m_case.y-titleSize, titleSize, BLACK);
}

void TextCase::getText(char *text)
{
    strcpy(text, m_text.c_str());
}

void TextCase::clearText()
{
    m_text = "";
}

void TextCase::setTitle(const char *title)
{
    m_title = title;
}

void TextCase::setValid(std::unordered_set<char> &valid)
{
    m_valid = new std::unordered_set<char>(valid);
}

void TextCase::unSelect()
{
    m_isUsing = false;
}