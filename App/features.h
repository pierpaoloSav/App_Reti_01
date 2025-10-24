#pragma once

#include "functions.h"

char findClass(u_int8_t ip[4]);

bool isPrivate(u_int8_t ip[4]);

bool sameNet(u_int8_t ip[4], u_int8_t ip1[4], u_int8_t sm[4]);