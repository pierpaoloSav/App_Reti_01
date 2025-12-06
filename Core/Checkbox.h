#pragma once

#include <raylib.h>

/*
Classe che permette la creazione di semplici checkbox:
-Vengono selezionate e deselezionate
-Comprendono un titolo da passare al costruttore
-Il click viene verificato tramite la funzione event
-Lo stato della checkbox(selezionata o no) viene preso con getStatus
*/

class Checkbox
{
public:
    Checkbox(float posX, float posY, int side, const char* title);

    void event();
    bool getStatus();
    
    void render();
    
private:
    Rectangle m_case;
    const char* m_title;

    bool m_status;
    bool m_down;
};