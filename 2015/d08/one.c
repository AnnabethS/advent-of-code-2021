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
	int codeLength = strlen(str);
	int actualLength = codeLength - 2; // this accounts for the 2 guaranteed " characters
	char* nextSlash = strchr(str, '\\');
	while(nextSlash != NULL)
	{
		if(*(nextSlash+1) == 'x')
		{
			actualLength -= 3;
			nextSlash += 4;
		}
		else
		{
			actualLength -= 1;
			nextSlash += 2;
		}
		nextSlash = strchr(nextSlash, '\\');
	}
	return codeLength - actualLength;
}
