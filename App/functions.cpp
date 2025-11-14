#include "functions.h"

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

bool isAnIp(bool ip[32])
{
    //verify ip is not over class C
    int i = 0;
    while(ip[i])
    {
        if(i == 2)
            return false;

        i++;
    }
    
    return true;
}

bool isSubnetMask(bool sm[32])
{
    //verify it has only 1 on the left and 0 right
    bool host = false;
    for (int i = 0; i < 32; i++)
    {
        if (!host and !sm[i])
            host = true;

        if (host and sm[i])
            return false;
    }
    
    return true;
}

bool isNetId(bool ip[32], uint8_t netBits)
{
    //verify it hasn't 1s in the host id
    for (int i = netBits; i < 32; i++)
        if (ip[i])
            return false;

    return true;
}

void convertIp(char *ipS, bool ip[32])
{
    //THE ADDRES HAS TO BE VALID

    //conversion in decimal
    char octet[5] = "";
    u_int8_t ipN[4];
    int t = 0;
    int d = 0;

    for (int i = 0; i < strlen(ipS)+1; i++)
    {
        if (ipS[i] == '.' || ipS[i] == '\0')
        {
            //get octet num and append
            int n = atoi(octet);
            ipN[d] = n;
            d++;

            //reset octet
            t=0;
            octet[0] = '\0';
            continue;
        }

        //octet update
        octet[t] = ipS[i];
        t++;
        octet[t] = '\0';
    }

    //conversion in binary with module method
    int k = 3;
    for (int i = 0; i < 4; i++)
    {
        int n = ipN[i];
        for (int j = 0; j < 8; j++)
        {
            ip[32-(k*8)-j-1] = n%2;
            n /= 2;
        }
        k--;
    }
}

void convertIpString(bool ip[32], char *ipS)
{
    //THE ADDRES HAS TO BE VALID

    //conversion from binary
    u_int8_t ipN[4];
    for (int i = 0; i < 4; i++)
    {
        int n = 0;
        int k = 0;
        for (int j = 7+(i*8); j >= i*8; j--)
        {
            n += ip[j] * pow(2, k);
            k++;
        }
        
        ipN[i] = n;
    }

    //conversion from decimal
    int j = 0;
    for (int i = 0; i < 4; i++)
    {
        char octet[5];
        snprintf(octet, sizeof(octet), "%d", ipN[i]);
        if (i!=3)
        {
            octet[strlen(octet)+1] = '\0';
            octet[strlen(octet)] = '.';
        }

        strcpy(ipS+j, octet);
        j += strlen(octet);
    }
}