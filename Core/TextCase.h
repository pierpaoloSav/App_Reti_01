#pragma once

#include <raylib.h>
#include <string>
#include <unordered_set>

class TextCase
{
public:
    TextCase(float posX, float posY, int width, int height, int fontSize, int max);
    ~TextCase();

    void event();
    void render();
    
    void getText(char *text);

    void setTitle(const char* title);
    void setValid(std::unordered_set<char> valid);

private:
    Rectangle m_case;

    const char* m_title;
    std::string m_text;
    int m_fontSize;
    int m_max;
    std::unordered_set<char> *m_valid;
    bool m_isUsing;
};