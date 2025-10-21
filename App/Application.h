#pragma once

#include "Window.h"
#include "TextCase.h"
#include "Button.h"

class Application
{
public:
    Application(int screenWidth, int screenHeight, const char* title);
    ~Application();

    void run();

private:
    void Loop();
    void Render();

    void InitIpCase();
    void InitIpCase1();
    void InitSmCase();

    void SelectMod();

private:
    Window window;

    TextCase *ipCase;
    TextCase *ipCase1;
    TextCase *smCase;

    uint8_t nMod;
    Button plus;
    Button minus;

    Button calculate;
};