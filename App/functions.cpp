#include "functions.h"

#include <iostream>
#include <stdlib.h>

bool inputIpValid(char *ip)
{
    char octet[5] = "";
    int t = 0;

    //dot counter
    int d = 0;

    for (int i = 0; i < strlen(ip)+1; i++)
    {
        if (ip[i] == '.' || ip[i] == '\0')
        {
            //increment dots
            d++;

            //check the number
            if (t == 0)
                return false;
            int n = atoi(octet);
            if (n<0 || n>255)
                return false;

            //reset octet
            t=0;
            octet[0] = '\0';
            continue;
        }

        //octet update
        octet[t] = ip[i];
        t++;
        octet[t] = '\0';

        //check if the number is too long
        if (t > 3)
            return false;
    }
    //must have 3 dots + the '\0'
    if (d!=4)
        return false;

    return true;
}