#pragma once

#include "headers.h"
#include "functions.h"
void binarySum(bool ip[32], bool ip1[32]); //forward declaration

struct net
{
    bool netId[32];
    bool h1[32];
    bool h2[32];
    bool gateway[32];
    bool broadcast[32];
    bool sm[32];

    bool created = false;
    bool m_bGat;
    int m_cidr = 0;
    int m_nSubnet = 0;
    
    void create(bool id[32], u_int8_t netBit, int nSubnet, bool bGat)
    { 
        m_bGat = bGat;
        m_nSubnet = nSubnet;
        m_cidr = netBit;

        memcpy(netId, id, sizeof(bool)*32); 

        memcpy(h1, netId, sizeof(bool)*32); 
        h1[31] += 1;

        memcpy(broadcast, netId, sizeof(bool)*32); 
        for (int i = netBit; i < 32; i++)
            broadcast[i] = 1;

        if (bGat)
        {
            memcpy(gateway, broadcast, sizeof(bool)*32); 
            gateway[31] -= 1;

            memcpy(h2, broadcast, sizeof(bool)*32); 
            {
                //two's complement of two
                bool two[32];
                memset(two, 0, 32);
                two[30] = 1;
                bool change = false;
                for (int i = 31; i >= 0; i--)
                {
                    if (change) two[i] = !two[i];
                    if (two[i]) change = true; 
                }            

                //sum
                binarySum(h2, two);
            }
        }
        else
        {
            memcpy(h2, broadcast, sizeof(bool)*32); 
            h2[31] -= 1;
        }

        memset(sm, 0, 32);
        for (int i = 0; i < netBit; i++)
            sm[i] = 1;

        created = true;
    }
};