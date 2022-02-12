#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFLEN 30000

char* input;

int main()
{
	input = calloc(BUFLEN, sizeof(char));
	FILE* fp = fopen("input.txt", "r");
	fscanf(fp, "%s", input);
	fclose(fp);
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
			total += x;
			lastCharWasNum = 0;
			memset(numBuffer, 0, sizeof(char)*10);
		}
	}
	printf("total: %d\n", total);
}
