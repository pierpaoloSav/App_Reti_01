#include "Application.h"

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