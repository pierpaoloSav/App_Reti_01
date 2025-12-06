#include "Application.h"

Application::Application(int screenWidth, int screenHeight, const char* title) :
    window(screenWidth, screenHeight, title), 

    nMod(1),

    //Textcases
    ipCase(nullptr),
    ipCase1(nullptr),
    smCase(nullptr),
    nSubnetCase(nullptr),
    subnetToView(nullptr),
    nHostCase(nullptr),

    nHostsInput(false),

    //Buttons
    plus(620+50, 110, 20, 20, "+", 10),
    minus(620+130, 110, 20, 20, "-", 10),
    change(nullptr),
    b_change(false),

    calculate(620+50, 160, 100, 20, "CALCOLA", 15),
    description(""),

    //Checkboxes
    binaryCheckbox(620+50, 200, 20, "01"),
    gatewayCheckBox(620+130, 200, 20, "gateway"),
    binary(false),

    inputError(false),
    outputS(""),
    Table(nullptr),
    outputTable(nullptr),
    tableCols(14)
{
    this->SelectMod();
}

Application::~Application()
{
    if(ipCase)
    {
        delete ipCase;
        ipCase = nullptr;
    }
    if(ipCase1)
    {
        delete ipCase1;
        ipCase1 = nullptr;
    }
    if(smCase)
    {
        delete smCase;
        smCase = nullptr;
    }
    if (nSubnetCase)
    {
        delete nSubnetCase;
        nSubnetCase = nullptr;
    }
    if (subnetToView)
    {
        delete subnetToView;
        subnetToView = nullptr;
    }
    if (nHostCase)
    {
        delete nHostCase;
        nHostCase = nullptr;
    }
    if (change)
    {
        delete change;
        change = nullptr;
    }

    delete[] Table;
    Table = nullptr;

    delete[] outputTable;
    outputTable = nullptr;
}

void Application::run()
{
    while (window.isOpen())
    {
        this->Loop();
        this->Render();
    }
}