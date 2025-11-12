#pragma once

#include <iostream>
#include <stdlib.h>
#include <string.h>

bool inputIpValid(char *ip);

bool isAnIp(char *ip);

bool isSubnetMask(char *sm);

void convertIp(char *ipS, bool ip[32]);

void convertIpString(bool ip[32], char *ipS);