#include "Application.h"

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