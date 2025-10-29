#pragma once

#include <raylib.h>
#include <string.h>
#include <unordered_set>
#include <iostream>

/*
Classe che permette la creazione di semplici caselle di testo:
-Il testo può essere preso come array di caratteri tramite il
 metodo getText
-Il testo può essere cancellato tramite il metodo clearText
-Sono evidenziati quando selezionati
-Comprendono un piccolo titolo inseiribile sopra di esse tramite
 il metodo setTitle
-Possono essere inserite delle restrizioni per i caratteri scritti
 tramite il metodo setValid, che prende un hashset contenente i
 caratteri validi
*/

class TextCase
{
public:
    TextCase(float posX, float posY, int width, int height, int max);
    ~TextCase();

    void event();
    void render();
    
    void getText(char *text);
    void clearText();

    void setTitle(const char* title);
    void setValid(std::unordered_set<char> &valid);

private:
    Rectangle m_case;

    const char* m_title;
    std::string m_text;
    int m_fontSize;
    int m_max;
    std::unordered_set<char> *m_valid;

    bool m_down;
    bool m_isUsing;
};