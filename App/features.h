#pragma once

#include "headers.h"
#include "functions.h"

/*
Tutte le funzionalità dell'applicazione
*/

//MOD 1
char findClass(bool ip[32]);

bool isPrivate(bool ip[32]);

//MOD 2
bool sameNet(bool ip[32], bool ip1[32], bool sm[32]);

//MOD 3
bool subnetting(bool ip[32], int nSubnets, int subnetRequired, net* table, int nEffSubnets, bool gateway);

//MOD 4
bool vlsmSubnetting(bool ip[32], int nSubnets, int *nHosts, net *table, bool gateway);