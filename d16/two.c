#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "hexUtils.h"

#ifdef TEST
#define FILENAME "test.txt"
#define HEXSTRINGLEN 26
#define BINSTRINGLEN HEXSTRINGLEN*4
#else
#define FILENAME "input.txt"
#define HEXSTRINGLEN 1400
#define BINSTRINGLEN HEXSTRINGLEN*4
#endif

typedef struct link_i{
    long long data;
    struct link_i *next;
}link_i;

// endOfRead will be the address it stopped reading data at,
// NOT the end of the packet
long long getLiteralPacketValue(char *str, char **endOfRead);

long long readOperatorPacket(char *str, char **endOfRead);

//pEnd will be set to the address of the start of the next packet
long long readPacket(char *pStart, char **pEnd, char fill);
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
    }
    
    char *currPacket = binStringStart;
    long long val = readPacket(currPacket, &currPacket, 1);
    printf("total: %lld", val);

}

long long readPacket(char *pStart, char **pEnd, char fill)
{
    int packetType = binaryStringToInt(pStart+3, 3);

    char *endOfRead;

    long long packetValue = 0;

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

long long readOperatorPacket(char *str, char **endOfRead)
{
    long long packetValue = 0;
    int type = binaryStringToInt(str+3, 3);
    if(type == 4)
    {
        printf("literal packet passed to readOperatorPacket:\n %s", str);
    }

    char lengthType = *(str+6)=='1';

    link_i *listStart = malloc(sizeof(link_i));
    link_i *listHead = listStart;
    listHead->data = -1;
    listHead->next = NULL;

    if(lengthType)
    {//the next 11 bits starting with str+8 are the number of packets
        int numPackets = binaryStringToInt(str+7, 11);
        char *packetStart = str+7+11;
        for(int i=0; i < numPackets; i++)
        {
            listHead->data = readPacket(packetStart, &packetStart, 0);
            listHead->next = malloc(sizeof(link_i));
            listHead = listHead->next;
            listHead->next = NULL;
        }
        *endOfRead = packetStart;
    }
    else
    {
        // the next 15 bits starting with str+8 are the number of bits used
        // by the packets
        int bitsUsed = binaryStringToInt(str+7, 15);
        char *subPacketStart = str+7+15;
        char *currSubPacket = subPacketStart;
        while(currSubPacket - subPacketStart < bitsUsed)
        {
            listHead->data = readPacket(currSubPacket, &currSubPacket, 0);
            listHead->next = malloc(sizeof(link_i));
            listHead = listHead->next;
            listHead->next = NULL;
        }
        *endOfRead = currSubPacket;
    }
    link_i *ptr = listStart;
    packetValue = 0;

    ptr = listStart;
    
    switch(type)
    {
    case(0):
        //sum
        while(ptr->next != NULL)
        {
            packetValue += ptr->data;
            ptr = ptr->next;
        }
        break;
    case(1):
        //product
        packetValue = 1;
        while(ptr->next != NULL)
        {
            packetValue *= ptr->data;
            ptr = ptr->next;
        }
        break;
    case(2):
        //min
        packetValue = LLONG_MAX;
        while(ptr->next != NULL)
        {
            if(ptr->data < packetValue)
                packetValue = ptr->data;
            ptr = ptr->next;
        }
        break;
    case(3):
        //max
        packetValue = LLONG_MIN;
        while(ptr->next != NULL)
        {
            if(ptr->data > packetValue)
                packetValue = ptr->data;
            ptr = ptr->next;
        }
        break;
    case(5):
        //greater than
        packetValue = (ptr->data) > (ptr->next->data);
        break;
    case(6):
        //less than
        packetValue = (ptr->data) < (ptr->next->data);
        break;
    case(7):
        // equal to
        packetValue = (ptr->data) == (ptr->next->data);
        break;
    }
    return packetValue;
}

long long getLiteralPacketValue(char *str, char **endOfRead)
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
    long long val = binaryStringToInt(outputString, stringSize);
    return val;
}

void printChars(char *str, int numChars)
{
    for(int i=0; i < numChars; i++)
    {
        printf("%c", *(str+i));
    }
    printf("\n");
}
