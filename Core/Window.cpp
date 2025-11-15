#include "Window.h"

Window::Window(int width, int height, const char* title) :
    m_width(width),
    m_height(height)
{
    InitWindow(m_width, m_height, title);
}

Window::~Window()
{
    CloseWindow();
}

int Window::getWidth()
{
    return m_width;
}

int Window::getHeight()
{
    return m_height;
}

bool Window::isOpen()
{
    return !WindowShouldClose();
}