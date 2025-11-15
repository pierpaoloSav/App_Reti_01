#pragma once

#include "headers.h"
#include "functions.h"

char findClass(bool ip[32]);

bool isPrivate(bool ip[32]);

bool sameNet(bool ip[32], bool ip1[32], bool sm[32]);

bool subnetting(bool ip[32], int nSubnets, int subnetRequired, net* table, int nEffSubnets);