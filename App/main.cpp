#include "Application.h"

int main()
{
    const char *Title = "APP RETI 01";

    Application app(1440, 720, Title);
    app.run();
}

//TODO: review Application.cpp