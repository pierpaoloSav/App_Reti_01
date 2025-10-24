#include "Application.h"

Application::Application(int screenWidth, int screenHeight, const char* title) :
    window(screenWidth, screenHeight, title), //? cambiare window e farla pointer??

    nMod(1),

    //Textcases
    ipCase(nullptr),
    ipCase1(nullptr),
    smCase(nullptr),
    nSubnetCase(nullptr),
    subnetToView(nullptr),
    nHostCase(nullptr),

    //Buttons
    plus(570, 110, 20, 20, "+", 10),
    minus(630, 110, 20, 20, "-", 10),

    calculate(50, 240, 100, 20, "CALCULATE", 15)
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
}

void Application::InitIpCase()
{
    ipCase = new TextCase(50, 50, 280, 30, 30, 15);
    ipCase->setTitle("IP 1");
    ipCase->setValid({'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'});
}

void Application::InitIpCase1()
{
    ipCase1 = new TextCase(50, 110, 280, 30, 30, 15);
    ipCase1->setTitle("IP 2");
    ipCase1->setValid({'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'});
}

void Application::InitSmCase()
{
    smCase = new TextCase(50, 170, 280, 30, 30, 15);
    smCase->setTitle("Subnet Mask");
    smCase->setValid({'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'});
}

void Application::InitNSubnetCase()
{
    nSubnetCase = new TextCase(50, 110, 280, 30, 30, 7);
    nSubnetCase->setTitle("Numero di Sottoreti");
    nSubnetCase->setValid({'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'});
}

void Application::InitSubnetToView()
{
    subnetToView = new TextCase(50, 170, 280, 30, 30, 7);
    subnetToView->setTitle("Sottorete da visualizzare");
    subnetToView->setValid({'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'});
}

void Application::InitNHostCase()
{
    nHostCase = new TextCase(50, 170, 280, 30, 30, 7);
    nHostCase->setTitle("Sottorete da visualizzare");
    nHostCase->setValid({'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'});
}

void Application::run()
{
    while (window.isOpen())
    {
        this->Loop();
        this->Render();
    }
}

void Application::SelectMod()
{
    //delete current
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
    if(nSubnetCase)
    {
        delete nSubnetCase;
        nSubnetCase = nullptr;
    }
    if(subnetToView)
    {
        delete subnetToView;
        subnetToView = nullptr;
    }
    if(nHostCase)
    {
        delete nHostCase;
        nHostCase = nullptr;
    }
    //create news
    switch (nMod)
    {
    case 1:
        InitIpCase();
        break;
    case 2:
        InitIpCase();
        InitIpCase1();
        InitSmCase();
        break;
    case 3:
        InitIpCase();
        InitNSubnetCase();
        InitSubnetToView();
        break;
    case 4:
        InitIpCase();
        InitNSubnetCase();
        InitNHostCase();
        
        break;
    default:
        std::cout << "ERROR: wrong mod value" << "\n";
        break;
    }
}

bool Application::Processing()
{
    //collect the data and check it
    char ipS[16] = "";
    if (ipCase)
    {
        ipCase->getText(ipS);
        if (!inputIpValid(ipS) || !isAnIp(ipS))
            return false;
    }
        
    char ip1S[16] = "";
    if(ipCase1)
    {
        ipCase1->getText(ip1S);
        if (!inputIpValid(ip1S) || !isAnIp(ip1S))
            return false;
    }

    char smS[16];
    if(smCase)
    {
        smCase->getText(smS);
        if (!inputIpValid(smS) || !isSubnetMask(smS))
            return false;
    }

    //process the data
    switch (nMod)
    {
    case 1:
    {
        u_int8_t ip[4];
        convertIp(ipS, ip);

        std::cout << "Classe: " << findClass(ip) << "\n";
        if (isPrivate(ip))
            std::cout << "Indirizzo privato\n";
        else
            std::cout << "Indirizzo pubblico\n";

        break;
    }
    case 2:
    {    
        u_int8_t ip[4];
        convertIp(ipS, ip);

        u_int8_t ip1[4];
        convertIp(ip1S, ip1);

        u_int8_t sm[4];
        convertIp(smS, sm);
        
        if (sameNet(ip, ip1, sm))
            std::cout << "Appartengono alla stessa rete\n";
        else
            std::cout << "Non appartengono alla stessa rete\n";

        break;
    }
    case 3:
        
        break;
    case 4:
        
        break;
    default:
        std::cout << "ERROR: wrong mod value" << "\n";
        break;
    }

    return true;
}

void Application::Loop()
{
    //--------INPUTS--------//
    if(ipCase)
        ipCase->event();
    if(ipCase1)
        ipCase1->event();
    if(smCase)
        smCase->event();
    if(nSubnetCase)
        nSubnetCase->event();
    if(subnetToView)
        subnetToView->event();
    if(nHostCase)
        nHostCase->event();
    bool b_plus = plus.pressed();
    bool b_minus = minus.pressed();
    bool b_calculate = calculate.pressed();

    //SELECTOR//
    if (b_plus && nMod < 4)
    {
        nMod++;
        this->SelectMod();
    }
    if (b_minus && nMod > 1)
    {
        nMod--;
        this->SelectMod();
    }
        
    //--------PROCESSING--------//
    if (b_calculate)
    {
        if (!this->Processing())
            std::cout << "Uno o più indirizzi non sono validi\n";
    }

    //--------OUTPUT--------//
}

void Application::Render()
{
    BeginDrawing();

        ClearBackground(WHITE);

        //textcases render
        if(ipCase)
            ipCase->render();
        if(ipCase1)
            ipCase1->render();
        if(smCase)
            smCase->render();
        if(nSubnetCase)
            nSubnetCase->render();
        if(subnetToView)
            subnetToView->render();
        if(nHostCase)
            nHostCase->render();

        //selector render 
            //title render
            DrawText("Selezionare\nModalità", 520, 30, 30, BLACK);
            //value render
            std::string buff = std::to_string(nMod);
            DrawText(buff.c_str(), 610-(MeasureText(buff.c_str(), 20)/2), 110, 20, BLACK);
            //buttons render
            plus.render();
            minus.render();

        calculate.render();

    EndDrawing();
}