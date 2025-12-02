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

bool subnetting(bool ip[32], int nSubnets, int subnetRequired, net* table, int nEffSubnets, bool gateway)
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
        table[i].create(netId, e+1, k, gateway);
    }

    return true;
}

bool vlsmSubnetting(bool ip[32], int nSubnets, int *nHosts, net *table, bool gateway)
{
    //get the class
    int cidr = ((int)findClass(ip)-96) * 8; //? classless o classfull solo

    //sort hosts
    int sortedHosts[nSubnets];
    memcpy(sortedHosts, nHosts, sizeof(int)*nSubnets);
    bubbleSortDesc(sortedHosts, nSubnets);

    bool netId[32];
    memcpy(netId, ip, sizeof(bool)*32);
    for (int i = 0; i < nSubnets; i++)
    {
        //get current cidr
        int cCidr = 32 - log2(sortedHosts[i]+(2+(int)gateway));
        if (cCidr <= cidr)
            return false;

        //add the subnet in the input order
            //get the number of the subnet
            int n = 0;
            for (; n < nSubnets && sortedHosts[i] != nHosts[n]; n++);
            nHosts[n] = -1;

            //build a ordered table
            int k = i-1;
            if (k != -1 && table[k].m_nSubnet > (n+1))
            {
                //shift 
                while (k != -1 && table[k].m_nSubnet > (n+1))
                {
                    table[k+1] = table[k];
                    k--;
                }

                table[k+1].create(netId, cCidr, (n+1), gateway);
            }
            else
                table[i].create(netId, cCidr, (n+1), gateway);

        //save the old netId for control
        bool oldNetId[32];
        memcpy(oldNetId, netId, sizeof(bool)*32);

        //get newNetId
        bool toSum[32] = {0};
        toSum[cCidr-1] = 1;
        binarySum(netId, toSum);

        //subnet error if the sum modified the original netId
        for (int j = 0; j < cidr; j++) 
        {
            if (netId[j] != oldNetId[j])
            return false;
        }
    }

    return true;
}