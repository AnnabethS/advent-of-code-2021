#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFLEN 30000

int getValueOfObject(char* ptr);
void excludeObject(char* ptr);
char isObject(char* ptr);

char* input;
char* excluded;

int main()
{
	input = calloc(BUFLEN, sizeof(char));
	excluded = calloc(BUFLEN, sizeof(char));
	FILE* fp = fopen("input.txt", "r");
	fscanf(fp, "%s", input);
	fclose(fp);
	char* nextRed = strstr(input, "red");
	int reds = 0;
	while(nextRed != NULL)
	{
		reds++;
		if(isObject(nextRed))
		{
			excludeObject(nextRed);
		}
		nextRed++;
		nextRed = strstr(nextRed, "red");
	}
	printf("reds_found: %d\n", reds);
	char lastCharWasNum = 0;
	char numBuffer[10] = {0};
	int total = 0;
	for(int i=0; i < BUFLEN && input[i]; i++)
	{
		if(input[i] == '-' || (input[i] >= '0' && input[i] <= '9'))
		{
			strncat(numBuffer, &input[i], 1);
			lastCharWasNum = 1;
		}
		else if(lastCharWasNum)
		{
			int x = strtol(numBuffer, NULL, 10);
			if(!excluded[i])
				total += x;
			lastCharWasNum = 0;
			memset(numBuffer, 0, sizeof(char)*10);
		}
	}
	printf("total: %d\n", total);
}

char isObject(char* ptr)
{
	while(*ptr != '{' && *ptr != '[')
	{
		ptr--;
	}
	return *ptr == '{';
}

void excludeObject(char* ptr)
{ //can be passed any pointer within an object
	while(*ptr != '{')
	{
		ptr--;
	}
	//ptr now points at the start of the object
	char* objStart = ptr;
	int openingBraces = 1;
	ptr++;
	while(openingBraces > 0)
	{
		if(*ptr == '{')
			openingBraces++;
		else if(*ptr == '}')
			openingBraces--;
		ptr++;
	}
	char* objEnd = ptr;
	int objLen = objEnd - objStart;
	int logicalStart = objStart - input;
	char testBuf[BUFLEN] = {0};
	strncpy(testBuf, objStart, objLen);
	printf("%s\n", testBuf);
	memset(excluded + logicalStart, 1, sizeof(char)*objLen);
}

int getValueOfObject(char* ptr)
{ //ptr must be the location of an opening brace for an object
	if(*ptr != '{')
	{
		printf("getValueOfObject passed a wrong pointer. UNDEFINED BEHAVIOUR...\n");
		return 0;
	}
	int openingBraces = 1;
	int total = 0;
	ptr++;
	while(openingBraces > 0)
	{
		printf("%c", *ptr);
		if(*ptr >= '0' && *ptr<= '9')
		{
			int x = strtol(ptr, &ptr, 10);
			ptr--;
			printf("\n%d\n", x);
			total += x;
		}
		else if(*ptr == '{')
			openingBraces++;
		else if(*ptr == '}')
			openingBraces--;
		ptr++;
	}
	return total;
}
