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
    plus(470, 110, 20, 20, "+", 10),
    minus(550, 110, 20, 20, "-", 10),

    calculate(470, 160, 100, 20, "CALCULATE", 15),
    description(""),

    inputError(false),
    outputS(""),
    outputTable(nullptr),
    tableCols(7)
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

    delete[] outputTable;
    outputTable = nullptr;
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
    if(ipCase && !nHostsInput)
        ipCase->event();
    if(ipCase1)
        ipCase1->event();
    if(smCase)
        smCase->event();
    if(nSubnetCase && !nHostsInput)
        nSubnetCase->event();
    if(subnetToView)
        subnetToView->event();
    if(nHostCase && nHostsInput)
        nHostCase->event();
    bool b_plus = plus.pressed();
    bool b_minus = minus.pressed();
    bool b_calculate = calculate.pressed();

    //SELECTOR//
    if (b_plus && nMod < 4 && !nHostsInput)
    {
        nMod++;
        this->SelectMod();
    }
    if (b_minus && nMod > 1 && !nHostsInput)
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
            int xOff = 420;
            int yOff = 30;
            DrawText("Selezionare", xOff+100-(MeasureText("Selezionare", 30)/2), yOff, 30, BLUE);
            DrawText("Modalità", xOff+100-(MeasureText("Modalità", 30)/2), yOff+30, 30, BLUE);
            //value render
            std::string buff = std::to_string(nMod);
            DrawText(buff.c_str(), xOff+90+10-(MeasureText(buff.c_str(), 20)/2), yOff+80, 20, BLACK);
            //description render
            DrawText(description.c_str(), xOff+200+100, yOff+30, 20, BLUE);
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

    description = "";

    //create new
    switch (nMod)
    {
    case 1:
        InitIpCase();

        description = "Dato un indirizzo IP\ndire di che classe è\ne se è un indirizzo privato";
        break;
    case 2:
        InitIpCase();
        InitIpCase1();
        InitSmCase();

        description = "Dato un indirizzo IP\ne Subnet Mask\ndire se appartengono\nalla stessa rete";
        break;
    case 3:
        InitIpCase();
        InitNSubnetCase();
        InitSubnetToView();

        description = "\nSUBNETTING FISSO";
        break;
    case 4:
        InitIpCase();
        InitNSubnetCase();
        InitNHostCase();
        
        description = "\nSUBNETTING VARIABILE\n(VLSM)";
        break;
    default:
        std::cout << "ERROR: wrong mod value" << "\n";
        break;
    }

    //clear output
    outputS = "";
    inputError = false;
    delete[] outputTable;
    outputTable = nullptr;
    nHostsInput = false;
}

void Application::Processing()
{
    //collect the data and check it
    char ipS[16] = "";
    if (ipCase)
    {
        ipCase->getText(ipS);

        if (!inputIpValid(ipS))
            inputError = true;
        else
            inputError = false;
    }
    
    char ip1S[16] = "";
    if(ipCase1)
    {
        ipCase1->getText(ip1S);

        if (!inputIpValid(ip1S))
            inputError = true;
        else
            inputError += false;
    }

    char smS[16] = "";
    if(smCase)
    {
        smCase->getText(smS);

        if (!inputIpValid(smS))
            inputError = true;
        else
            inputError += false;
    }

    char nSubnetS[7] = "";
    if (nSubnetCase)
        nSubnetCase->getText(nSubnetS);

    char toViewS[7] = "";
    if (subnetToView)
        subnetToView->getText(toViewS);

    char nHostS[7] = "";
    if (nHostCase)
    {
        nHostCase->getText(nHostS);
        nHostCase->clearText();
    }

    //error output
    if(inputError)
    {
        outputS = "Uno o più indirizzi non validi";
        return;
    }

    //process the data
    switch (nMod)
    {
    case 1:
    {
        //conversions
        bool ip[32];
        convertIp(ipS, ip);

        //process and get output
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
        //conversions
        bool ip[32];
        convertIp(ipS, ip);

        bool ip1[32];
        convertIp(ip1S, ip1);

        bool sm[32];
        convertIp(smS, sm);

        //mask error
        if(!isSubnetMask(sm))
        {
            outputS = "Subnet Mask errata";
            inputError = true;
            return;
        }
        
        //process and get output
        if (sameNet(ip, ip1, sm))
            outputS = "Appartengono alla\n stessa rete";
        else
            outputS = "Non appartengono alla\n stessa rete";

        break;
    }
    case 3:
    {
        //conversions
        bool ip[32];
        convertIp(ipS, ip);

        const int nSubnet = atoi(nSubnetS);

        int toView =  atoi(toViewS)-1;
        if(toView < 0) toView = 0;

        //ip error
        if(!isAnIp(ip))
        {
            outputS = "IP superiore alla classe c";
            inputError = true;
            return;
        }
        
        //process and get output
        outputTable = new net[tableCols];
        if(!subnetting(ip, nSubnet, toView, outputTable, tableCols))
        {
            //subnet error
            outputS = "Subnetting non calcolabile";
            inputError = true;
            delete[] outputTable;
            outputTable = nullptr;
            return;
        }
        
        break;
    }
    case 4:
    {
        static bool ip[32];
        static int nSubnet;
        static std::vector<int> nHosts;
        static int i = 0;

        if (!nHostsInput)
        {
            //conversions
            convertIp(ipS, ip);

            nSubnet = atoi(nSubnetS);
            
            //ip error
            if(!isAnIp(ip))
            {
                outputS = "IP superiore alla classe c";
                inputError = true;
                return;
            }

            //next phase, getting all nHosts
            nHostsInput = true;
        }
        else
        {    
            //get all nHosts
            if (i < nSubnet)
            {
                nHosts.push_back(atoi(nHostS));
                i++;
                if (nHosts[i-1] == 0)
                {
                    //subnet error
                    outputS = "Una rete non può avere 0 host";
                    inputError = true;
                    //delete table
                    delete[] outputTable;
                    outputTable = nullptr;
                    //go to the end
                    goto reset;
                }
                //continue only on the last input
                if (i != nSubnet)
                    return;
            }

            //process and get output
            outputTable = new net[tableCols];           //TODO: da input
            if(!vlsmSubnetting(ip, nSubnet, nHosts.data(), 5, outputTable, tableCols))
            {
                //subnet error
                outputS = "Subnetting non calcolabile";
                inputError = true;
                delete[] outputTable;
                outputTable = nullptr;
            }

            reset:
            //for static variables
            i = 0;
            nSubnet = 0;
            nHosts.clear();
            nHostsInput = false;
        }

        break;
    }
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
            //simple text output
            
            Color color = BLACK;
            if (inputError)
                color = RED;

            const char* text = outputS.c_str();
            int xOff = window.getWidth()/2;
            int yOff = 360;
            int textWidth = MeasureText(text, 50);
            DrawText(text, xOff-(textWidth/2), yOff-(50/2), 50, color);
            
            break;
        }
        case 3:
        case 4:
        {
            //simple text output for error
            if (inputError)
            {
                const char* text = outputS.c_str();
                int xOff = window.getWidth()/2;
                int yOff = 360;
                int textWidth = MeasureText(text, 50);
                DrawText(text, xOff-(textWidth/2), yOff-(50/2), 50, RED);
                break;
            }

            //SUBNETTING TABLE
            int xOff = 100; //size of number col
            int yOff = window.getHeight()/2;
            int cSize = 20;
            int col = 160;
            int row = 30;
            bool binary = false; //! RISOLVERE SITUAZIONE BINARY
            if (binary)
            {
                cSize = 5;
            }

            //table fields
            DrawText("NET-ID",   xOff         +(col/2-MeasureText("NET-ID", cSize)/2), yOff, cSize, BLACK);
            DrawText("1° H",     xOff +col    +(col/2-MeasureText("1° H", cSize)/2), yOff, cSize, BLACK);
            DrawText("Ultimo H", xOff +col*2  +(col/2-MeasureText("Ultimo H", cSize)/2), yOff, cSize, BLACK);
            DrawText("Gateway",  xOff +col*3  +(col/2-MeasureText("Gateway", cSize)/2), yOff, cSize, BLACK);
            DrawText("Broad.",   xOff +col*4  +(col/2-MeasureText("Broad.", cSize)/2), yOff, cSize, BLACK);
            DrawText("SM",       xOff +col*5  +(col/2-MeasureText("SM", cSize)/2), yOff, cSize, BLACK);
            
            //vertical lines
            DrawLine(xOff,        yOff-5, xOff,        window.getHeight(), BLACK);
            DrawLine(xOff +col,   yOff-5, xOff +col,   window.getHeight(), BLACK);
            DrawLine(xOff +col*2, yOff-5, xOff +col*2, window.getHeight(), BLACK);
            DrawLine(xOff +col*3, yOff-5, xOff +col*3, window.getHeight(), BLACK);
            DrawLine(xOff +col*4, yOff-5, xOff +col*4, window.getHeight(), BLACK);
            DrawLine(xOff +col*5, yOff-5, xOff +col*5, window.getHeight(), BLACK);
            
            //horizontal lines
            DrawLine(0, yOff-5,     window.getWidth(), yOff-5,     BLACK);
            DrawLine(0, yOff-5 +30, window.getWidth(), yOff-5 +30, BLACK);

            //values
            if(outputTable)
            {
                for (int i = 0; i < tableCols; i++)
                {
                    if (!outputTable[i].created)
                        continue;

                    //number col
                    std::string n = std::to_string(outputTable[i].m_nSubnet);
                    n.append("°");
                    DrawText(n.c_str(), (xOff/2-MeasureText(n.c_str(), cSize)/2), yOff +row +(i*row), cSize, BLACK);

                    char ipS[36] = "";
                    int textWidht;
                    
                    if (binary)
                        convertIpBinaryString(outputTable[i].netId, ipS);
                    else
                        convertIpString(outputTable[i].netId, ipS);
                    textWidht = MeasureText(ipS, cSize);
                    DrawText(ipS, xOff        +(col/2-textWidht/2), yOff +row +(i*row), cSize, BLACK);
                    
                    if (binary)
                        convertIpBinaryString(outputTable[i].h1, ipS);
                    else
                        convertIpString(outputTable[i].h1, ipS);
                    textWidht = MeasureText(ipS, cSize);
                    DrawText(ipS, xOff +col   +(col/2-textWidht/2), yOff +row +(i*row), cSize, BLACK);

                    if (binary)
                        convertIpBinaryString(outputTable[i].h2, ipS);
                    else
                        convertIpString(outputTable[i].h2, ipS);
                    textWidht = MeasureText(ipS, cSize);
                    DrawText(ipS, xOff +col*2 +(col/2-textWidht/2), yOff +row +(i*row), cSize, BLACK);

                    if (binary)
                        convertIpBinaryString(outputTable[i].gateway, ipS);
                    else
                        convertIpString(outputTable[i].gateway, ipS);
                    textWidht = MeasureText(ipS, cSize);
                    DrawText(ipS, xOff +col*3 +(col/2-textWidht/2), yOff +row +(i*row), cSize, BLACK);

                    if (binary)
                        convertIpBinaryString(outputTable[i].broadcast, ipS);
                    else
                        convertIpString(outputTable[i].broadcast, ipS);
                    textWidht = MeasureText(ipS, cSize);
                    DrawText(ipS, xOff +col*4 +(col/2-textWidht/2), yOff +row +(i*row), cSize, BLACK);

                    if (binary)
                        convertIpBinaryString(outputTable[i].sm, ipS);
                    else
                        convertIpString(outputTable[i].sm, ipS);
                    textWidht = MeasureText(ipS, cSize);
                    DrawText(ipS, xOff +col*5 +(col/2-textWidht/2), yOff +row +(i*row), cSize, BLACK);
                }
            }

            break;
        }
        default:
        {
            std::cout << "ERROR: wrong mod value" << "\n";
            break;
        }
    }
}