#pragma once

//?
#include <inttypes.h>
#include <iostream>
#include <string>
#include <unordered_set>

#include "Window.h"
#include "TextCase.h"
#include "Button.h"
#include "functions.h"
#include "features.h"

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
    void InitNSubnetCase();
    void InitSubnetToView();
    void InitNHostCase();

    void SelectMod();
    void Processing();
    void Output();

private:
    Window window;

    TextCase *ipCase;
    TextCase *ipCase1;
    TextCase *smCase;
    TextCase *nSubnetCase;
    TextCase *subnetToView;
    TextCase *nHostCase;

    uint8_t nMod;
    Button plus;
    Button minus;

    Button calculate;

    bool inputError;
    std::string outputS;
};