#pragma once

#include "headers.h"

/*
Funzioni necessarie per controllo, conversione
o altre operazioni sugli indirizzi IP
*/

bool inputIpValid(char *ip);

bool isAnIp(bool ip[32]);

bool isSubnetMask(bool sm[32]);

bool isNetId(bool ip[32], uint8_t netBits);

void convertIp(char *ipS, bool ip[32]);

void convertIpString(bool ip[32], char *ipS);

void convertIpBinaryString(bool ip[32], char *ipS);

void binarySum(bool ip[32], bool ip1[32]);

void bubbleSortDesc(int arr[], int n);