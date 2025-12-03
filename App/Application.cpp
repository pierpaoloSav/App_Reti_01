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
    plus(550+50, 110, 20, 20, "+", 10),
    minus(550+130, 110, 20, 20, "-", 10),
    change(nullptr),
    b_change(false),

    calculate(550+50, 160, 100, 20, "CALCOLA", 15),
    description(""),

    //Checkboxes
    binaryCheckbox(550+50, 200, 20, "01"),
    gatewayCheckBox(550+130, 200, 20, "gateway"),
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

    delete[] Table;
    Table = nullptr;

    delete[] outputTable;
    outputTable = nullptr;
}

void Application::InitIpCase()
{
    ipCase = new TextCase(50, 50, 280, 30, 15);
    ipCase->setTitle("IP");
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
    nHostCase = new TextCase(50, 230, 280, 30, 7);
    nHostCase->setTitle("Numero di Host");
    std::unordered_set<char> valid = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    nHostCase->setValid(valid);
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

    if(change)
    {
        delete change;
        change = nullptr;
    }

    if (Table)
    {
        delete[] Table;
        Table = nullptr;
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
        InitSubnetToView();
        InitNHostCase();
        change = new Button(340, 170, 50, 30, "CHANGE", 10);
        
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
    if(b_change) inputError = false;
    if(inputError)
    {
        outputS = "Uno o più indirizzi non validi";
        if (outputTable)
        {
            delete[] outputTable;
            outputTable = nullptr;
        }
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

        int toView =  MAX(atoi(toViewS)-1, 0);

        //ip error
        if(!isAnIp(ip))
        {
            outputS = "IP superiore alla classe c";
            inputError = true;
            return;
        }
        
        //process and get output
        if (outputTable)
        {
            delete[] outputTable;
            outputTable = nullptr;
        }
        outputTable = new net[tableCols-1];

        if(!subnetting(ip, nSubnet, toView, outputTable, tableCols-1, gatewayCheckBox.getStatus()))
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
        //not reset at the end
        static bool ip[32];
        static int nSubnet;
        static int toView = -1;

        //reset at the end
        static std::vector<int> nHosts;
        static int i = 0;

        if (!nHostsInput)
        {
            //-----------------//
            //toView change
            if (b_change)
            {
                if (nSubnet <= 0) return;

                toView = MAX(atoi(toViewS)-1, 0);

                //reallocate the output
                delete[] outputTable;
                outputTable = nullptr;
                outputTable = new net[tableCols-1];
                //define the output
                int diff = nSubnet-toView;
                if (diff >= tableCols-1) diff=0;
                if (diff > 0)
                    memcpy(outputTable, Table+toView, sizeof(net)*diff);
                else if (diff == 0)
                    memcpy(outputTable, Table+toView, sizeof(net)*(tableCols-1));

                return;
            }
            //else new subnetting
            //-----------------//

            //conversions
            convertIp(ipS, ip);

            if(atoi(nSubnetS) == 0) goto reset;
            nSubnet = atoi(nSubnetS);
            
            toView = MAX(atoi(toViewS)-1, 0);

            //ip error
            if(!isAnIp(ip))
            {
                outputS = "IP superiore alla classe c";
                inputError = true;
                goto reset;
            }

            //realloc a new Table
            if (Table)
            {
                delete[] Table;
                Table = nullptr;
            }
            Table = new net[nSubnet];

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
                    //go to the end
                    goto reset;
                }
                //continue only on the last input
                if (i != nSubnet)
                    return;
            }

            //process and get output
            if(!vlsmSubnetting(ip, nSubnet, nHosts.data(), Table, gatewayCheckBox.getStatus()))
            {
                //subnet error
                outputS = "Subnetting non calcolabile";
                inputError = true;
                //go to the end
                goto reset;
            }

            //get the outputTable
            if (outputTable)
            {
                delete[] outputTable;
                outputTable = nullptr;
            }
            outputTable = new net[tableCols-1];
            {
                //define the output
                int diff = nSubnet-toView;
                if (diff >= tableCols-1) diff=0;
                if (diff > 0)
                    memcpy(outputTable, Table+toView, sizeof(net)*diff);
                else if (diff == 0)
                    memcpy(outputTable, Table+toView, sizeof(net)*(tableCols-1));
            }

            reset:
            //for static variables
            i = 0;
            nHosts.clear();
            nHostsInput = false;
            if (inputError && outputTable)
            {
                delete[] outputTable;
                outputTable = nullptr;
            }
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
            int yOff = window.getHeight()/2;
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
                int yOff = window.getHeight()/2;
                int textWidth = MeasureText(text, 50);
                DrawText(text, xOff-(textWidth/2), yOff-(50/2), 50, RED);
                break;
            }

            //SUBNETTING TABLE
            int xOff = 100; //size of number col
            int yOff = 290;
            int cSize = 20;
            int vcSize = cSize;
            int col = 200;
            int row = 30;
            binary = binaryCheckbox.getStatus();
            if (binary) vcSize = 5;

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
                for (int i = 0; i < tableCols-1; i++)
                {
                    if (!outputTable[i].created)
                        continue;

                    //number col
                    std::string n = std::to_string(outputTable[i].m_nSubnet);
                    n.append("°");
                    DrawText(n.c_str(), (xOff/2-MeasureText(n.c_str(), cSize)/2), yOff +row +(i*row), cSize, BLACK);

                    char ipS[39] = "";
                    char cidrS[4] = "";
                    if (!binary) snprintf(cidrS, sizeof(cidrS), "/%d", outputTable[i].m_cidr);
                    int textWidht;
                    
                    if (binary)
                        convertIpBinaryString(outputTable[i].netId, ipS);
                    else
                    {
                        convertIpString(outputTable[i].netId, ipS);
                        strcat(ipS, cidrS);
                    }
                    textWidht = MeasureText(ipS, vcSize);
                    DrawText(ipS, xOff        +(col/2-textWidht/2), yOff +row +(i*row), vcSize, BLACK);
                    
                    if (binary)
                        convertIpBinaryString(outputTable[i].h1, ipS);
                    else
                    {
                        convertIpString(outputTable[i].h1, ipS);
                        strcat(ipS, cidrS);
                    }
                    textWidht = MeasureText(ipS, vcSize);
                    DrawText(ipS, xOff +col   +(col/2-textWidht/2), yOff +row +(i*row), vcSize, BLACK);

                    if (binary)
                        convertIpBinaryString(outputTable[i].h2, ipS);
                    else
                    {
                        convertIpString(outputTable[i].h2, ipS);
                        strcat(ipS, cidrS);
                    }
                    textWidht = MeasureText(ipS, vcSize);
                    DrawText(ipS, xOff +col*2 +(col/2-textWidht/2), yOff +row +(i*row), vcSize, BLACK);

                    if (outputTable[i].m_bGat)
                    {
                        if (binary)
                            convertIpBinaryString(outputTable[i].gateway, ipS);
                        else
                        {
                            convertIpString(outputTable[i].gateway, ipS);
                            strcat(ipS, cidrS);
                        }
                        textWidht = MeasureText(ipS, vcSize);
                        DrawText(ipS, xOff +col*3 +(col/2-textWidht/2), yOff +row +(i*row), vcSize, BLACK);
                    }

                    if (binary)
                        convertIpBinaryString(outputTable[i].broadcast, ipS);
                    else
                    {
                        convertIpString(outputTable[i].broadcast, ipS);
                        strcat(ipS, cidrS);
                    }
                    textWidht = MeasureText(ipS, vcSize);
                    DrawText(ipS, xOff +col*4 +(col/2-textWidht/2), yOff +row +(i*row), vcSize, BLACK);

                    if (binary)
                        convertIpBinaryString(outputTable[i].sm, ipS);
                    else
                        convertIpString(outputTable[i].sm, ipS);
                    textWidht = MeasureText(ipS, vcSize);
                    DrawText(ipS, xOff +col*5 +(col/2-textWidht/2), yOff +row +(i*row), vcSize, BLACK);
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
    bool b_plus = false;
    bool b_minus = false;
    bool b_calculate = calculate.pressed() || IsKeyPressed(KEY_ENTER);

    if(nHostCase && nHostsInput)
        nHostCase->event();
    else
    {
        if(ipCase) ipCase->event();
        if(ipCase1) ipCase1->event();
        if(smCase) smCase->event();
        if(nSubnetCase) nSubnetCase->event();
        if(subnetToView) subnetToView->event();

        b_plus = plus.pressed();
        b_minus = minus.pressed();
        if(change) b_change = change->pressed();
        binaryCheckbox.event();
        gatewayCheckBox.event();
    }

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
    if(b_change)
    {
        this->Processing();
        b_change = false;
    }
    if (b_calculate)
    {
        this->Processing();

        static bool old = false;
        if (old != nHostsInput)
        {
            if(ipCase) ipCase->unSelect();
            if(ipCase1) ipCase1->unSelect();
            if(smCase) smCase->unSelect();
            if(nSubnetCase) nSubnetCase->unSelect();
            if(subnetToView) subnetToView->unSelect();
            if(nHostCase) nHostCase->unSelect();
        }
        old = nHostsInput;
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
            int xOff = window.getWidth()/2;
            int yOff = 30;
            std::string buff;
            DrawText("Selezionare", xOff-(MeasureText("Selezionare", 30)/2), yOff, 30, BLUE);
            DrawText("Modalità", xOff-(MeasureText("Modalità", 30)/2), yOff+30, 30, BLUE);
            //value render
            buff = std::to_string(nMod);
            DrawText(buff.c_str(), xOff-(MeasureText(buff.c_str(), 20)/2), yOff+80, 20, BLACK);
            //Buttons render
            plus.render();
            minus.render();
            calculate.render();

        if(change)
            change->render();
        
        //description render
        DrawText(description.c_str(), xOff+200+100, yOff+30, 20, BLUE);
            
        //instruction for nHosts input
        buff = "Inserisci numero di host";
        if(nHostsInput)
            DrawText(buff.c_str(), xOff+200+100, yOff+120, 20, BLUE);
        
        //Checkboxes render
        binaryCheckbox.render();
        gatewayCheckBox.render();

        //--------OUTPUT--------//
        Output();

    EndDrawing();
}