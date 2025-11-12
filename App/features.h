#pragma once

#include "functions.h"

struct net
{
    bool netId[32];
    
    void create(bool id[32]) 
    { 
        memcpy(netId, id, sizeof(bool)*32); 
    }
};

char findClass(bool ip[32]);

bool isPrivate(bool ip[32]);

bool sameNet(bool ip[32], bool ip1[32], bool sm[32]);

bool subnetting(bool ip[32], int nSubnets, net* table);