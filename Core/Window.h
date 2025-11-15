#pragma once

#include <raylib.h>

class Window
{
public:
    Window(int width, int height, const char* title);
    ~Window();

    int getWidth();
    int getHeight();
    bool isOpen();
private:
    int m_width;
    int m_height;
};