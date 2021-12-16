#include "hexUtils.h"


long long binaryStringToInt(const char *str, const int length)
{
    char *tmp = (char*) calloc(length+1, sizeof(char));
    strncpy(tmp, str, length);
    long long result = strtol(tmp, NULL, 2);
    free(tmp);
    return result;
}


// str must be a pointer to a string of 4 (or more) chars, it will not null terminate
void hexCharToBin4String(const char hex, char *str)
{
    switch(hex)
    {
    case('0'):
        strcpy(str, "0000");
        break;
    case('1'):
        strcpy(str, "0001");
        break;
    case('2'):
        strcpy(str, "0010");
        break;
    case('3'):
        strcpy(str, "0011");
        break;
    case('4'):
        strcpy(str, "0100");
        break;
    case('5'):
        strcpy(str, "0101");
        break;
    case('6'):
        strcpy(str, "0110");
        break;
    case('7'):
        strcpy(str, "0111");
        break;
    case('8'):
        strcpy(str, "1000");
        break;
    case('9'):
        strcpy(str, "1001");
        break;
    case('A'):
        strcpy(str, "1010");
        break;
    case('B'):
        strcpy(str, "1011");
        break;
    case('C'):
        strcpy(str, "1100");
        break;
    case('D'):
        strcpy(str, "1101");
        break;
    case('E'):
        strcpy(str, "1110");
        break;
    case('F'):
        strcpy(str, "1111");
        break;
    default:
        printf("ERROR: hexCharToBin4String passed unknown char: %c", hex);
    }
}

char isHex(const char hexChar)
{
    return (hexChar >= 'A' && hexChar <= 'F') ||
        (hexChar >= '0' && hexChar <= '9');
}
