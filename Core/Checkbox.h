#pragma once

#include "raylib.h"

/*
*/

class Checkbox
{
public:
    Checkbox(float posX, float posY, int side);

    void event();
    bool getStatus();
    
    void render();
    
private:
    Rectangle m_case;

    bool m_status;
    bool m_down;
};
