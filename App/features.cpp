#include "features.h"

char findClass(u_int8_t ip[4])
{
    if (ip[0] < 128)
        return 'a';
    else if(ip[0] < 192)
        return 'b';
    else if(ip[0] < 224)
        return 'c';
    else //error
        return 'd';
}

bool isPrivate(u_int8_t ip[4])
{
    char ipClass = findClass(ip);

    switch (ipClass)
    {
    case 'a':
        if (ip[0] == 10)
            return true;
        break;
    case 'b':
        if (ip[0] == 172 && ip[1] >= 16 && ip[1] <= 31)
            return true;
    case 'c':
        if (ip[0] == 192 && ip[1] == 168)
            return true;
    default:
        return false;
        break;
    }
    
    return false;
}

bool sameNet(u_int8_t ip[4], u_int8_t ip1[4], u_int8_t sm[4])
{
    for (int i = 0; i < 4; i++)
    {
        bool ipB[32];
        convertIpBinary(ip, ipB);

        bool ip1B[32];
        convertIpBinary(ip1, ip1B);

        bool smB[32];
        convertIpBinary(sm, smB);
        
        for (int i = 0; i < 32; i++)
            if ((ipB[i] && smB[i]) != (ip1B[i] && smB[i]))
                return false;
    }

    return true;
}