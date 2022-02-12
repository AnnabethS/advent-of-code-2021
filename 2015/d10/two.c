#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFERLENGTH 5000000

char* backBuffer;
char* frontBuffer;

void doStep();

int main()
{
	backBuffer = calloc(BUFFERLENGTH, sizeof(char));
	frontBuffer = calloc(BUFFERLENGTH, sizeof(char));
	char* inputString = "1113222113";
	/* char* inputString = "111221"; */
	strcpy(frontBuffer, inputString);
	for(int i=0; i < 50; i++)
	{
		printf("%d\n", i);
		doStep();
	}
	unsigned long x = strlen(frontBuffer);
	printf("%lu\n", x);
}

void doStep()
{
	char* ptr = frontBuffer;
	char prevChar = *ptr;
	int prevCharCount = 0;
	while(prevChar != 0)
	{
		if(prevChar == *ptr)
		{
			prevCharCount++;
		}
		else
		{
			char section[3] = {0};
			section[0] = prevCharCount + '0';
			section[1] = prevChar;
			prevChar = *ptr;
			prevCharCount = 1;
			strcat(backBuffer, section);
		}
		ptr++;
	}
	memset(frontBuffer, 0, sizeof(char)*BUFFERLENGTH);
	strcpy(frontBuffer, backBuffer);
	memset(backBuffer, 0, sizeof(char)*BUFFERLENGTH);
}
