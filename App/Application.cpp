#include "Application.h"
#include "functions.h"

#include <iostream>
#include <string>
#include <unordered_set>

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
        
        break;
    case 4:
        
        break;
    default:
        std::cout << "ERROR: wrong mod value" << "\n";
        break;
    }
}

Application::Application(int screenWidth, int screenHeight, const char* title) :
    window(screenWidth, screenHeight, title),

    nMod(1),

    //Textcases
    ipCase(nullptr),
    ipCase1(nullptr),
    smCase(nullptr),

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
        char ip[16] = "";
        if(ipCase)
            ipCase->getText(ip);
        char ip1[16] = "";
        if(ipCase1)
            ipCase1->getText(ip1);
        
        std::cout << inputIpValid(ip) << " " << inputIpValid(ip1) << "\n";
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

