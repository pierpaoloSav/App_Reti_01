#include "Application.h"

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
            DrawText("n Host",   xOff +col*6  +(140/2-MeasureText("n Host", cSize)/2), yOff, cSize, BLACK);
            
            //vertical lines
            DrawLine(xOff,        yOff-5, xOff,        window.getHeight(), BLACK);
            DrawLine(xOff +col,   yOff-5, xOff +col,   window.getHeight(), BLACK);
            DrawLine(xOff +col*2, yOff-5, xOff +col*2, window.getHeight(), BLACK);
            DrawLine(xOff +col*3, yOff-5, xOff +col*3, window.getHeight(), BLACK);
            DrawLine(xOff +col*4, yOff-5, xOff +col*4, window.getHeight(), BLACK);
            DrawLine(xOff +col*5, yOff-5, xOff +col*5, window.getHeight(), BLACK);
            DrawLine(xOff +col*6, yOff-5, xOff +col*6, window.getHeight(), BLACK);
            
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

                    //n Host
                    n = std::to_string(outputTable[i].m_nHost);
                    DrawText(n.c_str(), xOff +col*6  +(140/2-MeasureText(n.c_str(), cSize)/2), yOff +row +(i*row), cSize, BLACK);
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