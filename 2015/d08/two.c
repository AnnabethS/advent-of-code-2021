#include <stdio.h>
#include <string.h>

#define BUFLEN 50

int getStringDiff(char* str);

int main()
{
	FILE* fp = fopen("input.txt", "r");
	char bufStr[BUFLEN] = {0};
	char eofcheck = fscanf(fp, "%s", bufStr);
	int diff = 0;
	while(eofcheck != EOF)
	{
		diff += getStringDiff(bufStr);
		eofcheck = fscanf(fp, "%s", bufStr);
	}
	printf("diff: %d\n", diff);
}

int getStringDiff(char* str)
{
	int actualLength = strlen(str);
	int codeLength = actualLength + 2; // this accounts for the 2 added "
	for(int i=0; i < actualLength; i++)
	{
		if(*(str+i) == '\\' || *(str+i) == '"')
			codeLength++;
	}
	return codeLength - actualLength;
}
