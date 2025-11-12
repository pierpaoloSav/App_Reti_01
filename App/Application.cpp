#include "Application.h"

Application::Application(int screenWidth, int screenHeight, const char* title) :
    window(screenWidth, screenHeight, title), //? cambiare window e farla pointer forse

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

    calculate(560, 160, 100, 20, "CALCULATE", 15),

    inputError(false),
    outputS("")
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
    ipCase = new TextCase(50, 50, 280, 30, 15);
    ipCase->setTitle("IP 1");
    std::unordered_set<char> valid = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'};
    ipCase->setValid(valid);
}

void Application::InitIpCase1()
{
    ipCase1 = new TextCase(50, 110, 280, 30, 15);
    ipCase1->setTitle("IP 2");
    std::unordered_set<char> valid = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'};
    ipCase1->setValid(valid);
}

void Application::InitSmCase()
{
    smCase = new TextCase(50, 170, 280, 30, 15);
    smCase->setTitle("Subnet Mask");
    std::unordered_set<char> valid = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'};
    smCase->setValid(valid);
}

void Application::InitNSubnetCase()
{
    nSubnetCase = new TextCase(50, 110, 280, 30, 7);
    nSubnetCase->setTitle("Numero di Sottoreti");
    std::unordered_set<char> valid = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    nSubnetCase->setValid(valid);
}

void Application::InitSubnetToView()
{
    subnetToView = new TextCase(50, 170, 280, 30, 7);
    subnetToView->setTitle("Sottorete da visualizzare");
    std::unordered_set<char> valid = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    subnetToView->setValid(valid);
}

void Application::InitNHostCase()
{
    nHostCase = new TextCase(50, 170, 280, 30, 7);
    nHostCase->setTitle("Numero di Host");
    std::unordered_set<char> valid = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    nHostCase->setValid(valid);
}

void Application::run()
{
    while (window.isOpen())
    {
        this->Loop();
        this->Render();
    }
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
        this->Processing();
    }
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

        //--------OUTPUT--------//
        Output();

    EndDrawing();
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

    //clear output
    outputS = "";
}

void Application::Processing()
{
    //collect the data and check it
    char ipS[16] = "";
    if (ipCase)
    {
        ipCase->getText(ipS);

        if ( !(inputIpValid(ipS) && isAnIp(ipS)) )
            inputError = true;
        else
            inputError = false;
    }
    
    char ip1S[16] = "";
    if(ipCase1)
    {
        ipCase1->getText(ip1S);

        if ( !(inputIpValid(ip1S) && isAnIp(ip1S)) )
            inputError = true;
        else
            inputError += false;
    }

    char smS[16];
    if(smCase)
    {
        smCase->getText(smS);

        if ( !(inputIpValid(smS) && isSubnetMask(smS)) )
            inputError = true;
        else
            inputError += false;
    }

    char nSubnetS[7];
    if (nSubnetCase)
        nSubnetCase->getText(nSubnetS);

    char toViewS[7];
    if (subnetToView)
        subnetToView->getText(toViewS);

    //process the data
    switch (nMod)
    {
    case 1:
    {
        //error output
        if(inputError)
        {
            outputS = "Uno o più indirizzi non validi";
            return;
        }

        bool ip[32];
        convertIp(ipS, ip);

        outputS = "Classe: ";
        outputS += findClass(ip);
        if (isPrivate(ip))
            outputS += "\nIndirizzo privato";
        else
            outputS += "\nIndirizzo pubblico";
        
        break;
    }
    case 2:
    {    
        //error output
        if(inputError)
        {
            outputS = "Uno o più indirizzi non validi";
            return;
        }
    
        bool ip[32];
        convertIp(ipS, ip);

        bool ip1[32];
        convertIp(ip1S, ip1);

        bool sm[32];
        convertIp(smS, sm);
        
        if (sameNet(ip, ip1, sm))
            outputS = "Appartengono alla\n stessa rete";
        else
            outputS = "Non appartengono alla\n stessa rete";

        break;
    }
    case 3:
    {
        //error output
        if(inputError)
        {
            outputS = "Uno o più indirizzi non validi";
            return;
        }

        //TODO: optimize

        bool ip[32];
        convertIp(ipS, ip);

        const int nSubnet = atoi(nSubnetS);
        int toView =  atoi(toViewS)-1;
        if (toView < 0) toView = 0;
        
        net Table[nSubnet];
        if (!subnetting(ip, nSubnet, Table))
        {
            outputS = "Subnetting non calcolabile";
            inputError = true;
            return;
        }

        memcpy(outputTable, Table+toView, sizeof(outputTable));
        
        break;
    }
    case 4:
        
        break;
    default:
        std::cout << "ERROR: wrong mod value" << "\n";
        break;
    }
}

void Application::Output()
{
    switch (nMod)
    {
        case 1:
        case 2:
        {
            Color color = BLACK;
            if (inputError)
                color = RED;

            const char* text = outputS.c_str();
            int textWidth = MeasureText(text, 50);
            DrawText(text, 360-(textWidth/2), 360-(50/2), 50, color);
            
            break;
        }
        case 3:
        {
            Color color = BLACK;
            if (inputError)
            {
                const char* text = outputS.c_str();
                int textWidth = MeasureText(text, 50);
                DrawText(text, 360-(textWidth/2), 360-(50/2), 50, RED);
                break;
            }

            //TODO: finire tabella
            for (int i = 0; i < sizeof(outputTable)/sizeof(outputTable[0]); i++)
            {
                char ipS[16];
                convertIpString(outputTable[i].netId, ipS);

                DrawText(ipS, 50, 240+(i*30)+30, 20, BLACK);
            }

            break;
        }
        case 4:
        {
           
            break;
        }
        default:
        {
            std::cout << "ERROR: wrong mod value" << "\n";
            break;
        }
    }
}