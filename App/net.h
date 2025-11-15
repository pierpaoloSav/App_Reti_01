#pragma once

#include "headers.h"

struct net
{
    bool netId[32];
    bool h1[32];
    bool h2[32];
    bool gateway[32];
    bool broadcast[32];
    bool sm[32];
    bool created = false;
    int m_nSubnet = 0;
    
    void create(bool id[32], u_int8_t netBit, int nSubnet)
    { 
        m_nSubnet = nSubnet;

        memcpy(netId, id, sizeof(bool)*32); 

        memcpy(h1, netId, sizeof(bool)*32); 
        h1[31] += 1;

        memcpy(broadcast, netId, sizeof(bool)*32); 
        for (int i = netBit; i < 32; i++)
            broadcast[i] = 1;

        memcpy(gateway, broadcast, sizeof(bool)*32); 
        gateway[31] -= 1;

        memcpy(h2, broadcast, sizeof(bool)*32); 
        {
            bool two[32];
            memset(two, 0, 32);
            two[30] = 1;

            for (int i = 0; i < 32; i++)
            {
                h2[i] = h2[i] && !(two[i]);
            }
        }

        memset(sm, 0, 32);
        for (int i = 0; i < netBit; i++)
            sm[i] = 1;

        created = true;
    }
};