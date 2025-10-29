#pragma once

#include <raylib.h>

/*
Classe che permette la creazione di semplici pulsanti:
-Reagiscono al click
-Comprendono un titolo da passare al costruttore
-Il click può essere verificato tramite il metodo pressed
*/

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