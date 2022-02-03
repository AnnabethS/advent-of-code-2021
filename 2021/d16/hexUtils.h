#ifndef ANNA_HEXUTILS
#define ANNA_HEXUTILS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void hexCharToBin4String(const char hex, char *str);
long long binaryStringToInt(const char *str, const int length);
char isHex(const char hex);

#endif
