#pragma once

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

bool inputIpValid(char *ip);

bool isAnIp(bool ip[32]);

bool isSubnetMask(bool sm[32]);

bool isNetId(bool ip[32], uint8_t netBits);

void convertIp(char *ipS, bool ip[32]);

void convertIpString(bool ip[32], char *ipS);