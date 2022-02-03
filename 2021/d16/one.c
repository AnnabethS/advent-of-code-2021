#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hexUtils.h"

#ifdef TEST
#define FILENAME "test.txt"
#define HEXSTRINGLEN 26
#define BINSTRINGLEN HEXSTRINGLEN*4
#else
#define FILENAME "input.txt"
#define HEXSTRINGLEN 1370
#define BINSTRINGLEN HEXSTRINGLEN*4
#endif

// endOfRead will be the address it stopped reading data at,
// NOT the end of the packet
int getLiteralPacketValue(char *str, char **endOfRead);

int readOperatorPacket(char *str, char **endOfRead);

//pEnd will be set to the address of the start of the next packet
int readPacket(char *pStart, char **pEnd, char fill);
void printChars(char *str, int numChars);

int main()
{
    FILE* fp = fopen(FILENAME, "r");

    char *binStringStart = calloc(BINSTRINGLEN, sizeof(char));
    {
        char nextChar = 'A';
        fscanf(fp, "%c", &nextChar);
        char *ptr = binStringStart;
        while(isHex(nextChar))
        {
            hexCharToBin4String(nextChar, ptr);
            ptr += 4;
            fscanf(fp, "%c", &nextChar);
        }
        /* printf("%s\n", binStringStart); */
    }

    /* printf("here\n"); */
    char *currPacket = binStringStart;
    int val = readPacket(currPacket, &currPacket, 1);
    printf("total packet value: %d", val);
}

int readPacket(char *pStart, char **pEnd, char fill)
{
    int packetType = binaryStringToInt(pStart+3, 3);

    char *endOfRead;

    int packetValue = 0;

    if(packetType==4)
    {
        packetValue = getLiteralPacketValue(pStart, &endOfRead);
    }
    else
    {
        packetValue = readOperatorPacket(pStart, &endOfRead);
    }

    if(fill)
    {
        int packetLength = endOfRead - pStart;
        int numHexChars = (packetLength / 4) + 1;
        *pEnd = pStart + numHexChars*4;
    }
    else
    {
        *pEnd = endOfRead;
    }
    return packetValue;
}

int readOperatorPacket(char *str, char **endOfRead)
{
    int packetValue = 0;
    packetValue += binaryStringToInt(str, 3);
    int type = binaryStringToInt(str+3, 3);
    if(type == 4)
    {
        printf("literal packet passed to readOperatorPacket:\n %s", str);
    }

    char lengthType = *(str+6)=='1';

    if(lengthType)
    {//the next 11 bits starting with str+8 are the number of packets
        int numPackets = binaryStringToInt(str+7, 11);
        char *packetStart = str+7+11;
        for(int i=0; i < numPackets; i++)
        {
            packetValue += readPacket(packetStart, &packetStart, 0);
        }
        *endOfRead = packetStart;
    }
    else
    {
        // the next 15 bits starting with str+8 are the number of bits used
        // by the packets
        int bitsUsed = binaryStringToInt(str+7, 15);
        printChars(str+7, 15);
        char *subPacketStart = str+7+15;
        char *currSubPacket = subPacketStart;
        printf("packet contents:\n");
        printChars(str+7+15, 27);
        while(currSubPacket - subPacketStart < bitsUsed)
        {
            packetValue += readPacket(currSubPacket, &currSubPacket, 0);
        }
        *endOfRead = currSubPacket;
    }
    return packetValue;
}

int getLiteralPacketValue(char *str, char **endOfRead)
{
    int type = binaryStringToInt(str+3, 3);
    if(type !=4)
    {
        printf("non-literal packet passed to getLiteralPacketValue:\n %s", str);
    }
    char *dataStart = str+6;
    char *data_ptr = dataStart;
    int stringSize = 4;
    char *outputString = calloc(stringSize+1, sizeof(char));
    strncat(outputString, data_ptr+1, 4);
    while(*data_ptr == '1')
    {
        stringSize += 4;
        outputString = reallocarray(outputString, stringSize+1, sizeof(char));
        data_ptr += 5;
        strncat(outputString, data_ptr+1, 4);
    }
    outputString = reallocarray(outputString, stringSize+1, sizeof(char));
    strncat(outputString, data_ptr+1, 4);
    data_ptr +=5;
    *endOfRead = data_ptr;
    int ver = binaryStringToInt(str, 3);
    /* return binaryStringToInt(outputString, stringSize); */
    return ver;
}

void printChars(char *str, int numChars)
{
    for(int i=0; i < numChars; i++)
    {
        printf("%c", *(str+i));
    }
    printf("\n");
}
