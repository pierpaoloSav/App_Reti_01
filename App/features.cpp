#include "features.h"

char findClass(bool ip[32])
{
    char result = 'a';

    for (int i = 0; ip[i] == 1 and result != 'e'; i++)
        result++;

    return result;
}

bool isPrivate(bool ip[32])
{
    char ipClass = findClass(ip);
    //convert first two octects
    int n = 0;
    int k = 0;
    int j = 0;
    for (int i = 7; i >= 0; i--)
    {
        n += ip[i] * pow(2, j);
        j++;
    }
    j=0;
    for (int i = 15; i >= 8; i--)
    {
        k += ip[i] * pow(2, j);
        j++;
    }

    switch (ipClass)
    {
    case 'a':
        if (n == 10)
            return true;
        break;
    case 'b':
        if (n == 172 && k >= 16 && k <= 31)
            return true;
    case 'c':
        if (n == 192 && k == 168)
            return true;
    default:
        return false;
        break;
    }
    
    return false;
}

bool sameNet(bool ip[32], bool ip1[32], bool sm[32])
{   
    for (int i = 0; i < 32; i++)
        if ((ip[i] && sm[i]) != (ip1[i] && sm[i]))
            return false;

    return true;
}

bool subnetting(bool ip[32], int nSubnets, int subnetRequired, net* table, int nEffSubnets)
{
    //calculate some vars
    const int nBit = ceil(log2(nSubnets));
    int s = ((int)findClass(ip)-96) * 8;
    int e = s+nBit -1;
    if (e > 29 || !isNetId(ip, s))
        return false; //? classless o classfull solo

    int k = subnetRequired;
    for (int i = 0; i < nEffSubnets && k < nSubnets; i++)
    {
        bool subId[nBit];
        bool netId[32];
        memcpy(netId, ip, sizeof(bool)*32);

        //get the subnet part and copy it in the netId
        int temp = k;
        for (int j = nBit-1; j >= 0; j--)
        {
            subId[j] = temp%2;
            temp /= 2;
        }
        k++;
        memcpy(netId+s, subId, sizeof(bool)*nBit);
        
        //add in the table
        table[i].create(netId, e+1, k);
    }

    return true;
}