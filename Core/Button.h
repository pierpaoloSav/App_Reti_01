#pragma once

#include <raylib.h>

class Button
{    
public:
    Button(float posX, float posY, int width, int height, const char* title, int fontSize);

    bool pressed();
    void render();
    
private:
    Rectangle m_case;

    const char* m_title;
    int m_fontSize;
    bool m_down;
};