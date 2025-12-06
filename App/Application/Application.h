#pragma once

#include "headers.h"
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

    //textcases inits
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
    
    bool nHostsInput;

    uint8_t nMod;
    Button plus;
    Button minus;

    Button calculate;
    Button *change;
    bool b_change;
    std::string description;

    Checkbox binaryCheckbox;
    Checkbox gatewayCheckBox;
    bool binary; 

    bool inputError;
    std::string outputS;
    net *Table;
    net *outputTable;
    const int tableCols;
};