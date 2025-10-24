#pragma once

#include <iostream>
#include <stdlib.h>
#include <string.h>

bool inputIpValid(char *ip);

bool isAnIp(char *ip);

bool isSubnetMask(char *sm);

void convertIp(char *ipS, uint8_t ip[4]);

void convertIpBinary(uint8_t ip[4], bool ipB[32]);