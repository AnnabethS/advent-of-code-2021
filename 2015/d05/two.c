#include <stdio.h>
#include <string.h>

#define BUFLEN 16

char isNice(char* str);

int main()
{
	FILE* fp = fopen("input.txt", "r");
	char buf[BUFLEN] = {0};
	char eofreached = fscanf(fp, "%s\n", &buf[0]);
	int niceCount = 0;
	while(eofreached != EOF)
	{
		if(isNice(&buf[0]))
		{
			niceCount++;
		}
		eofreached = fscanf(fp, "%s\n", &buf[0]);
	}
	printf("nice strings: %d\n", niceCount);
}

char isNice(char* str)
{
	// rule 1
	int len = strlen(str);
	char foundPairs = 0;
	for(int i=0; i < (len-1); i++)
	{
		char pair[3] = {0};
		strncpy(pair, (str+i), 2);
		for(int j=i+2; j < (len-1); j++)
		{
			if(strncmp(pair, (str+j), 2) == 0)
				foundPairs = 1;
		}
	}
	if(!foundPairs)
		return 0;

	// rule 2

	char foundSplit = 0;
	for(int i=0; i < (len-2); i++)
	{

		if(*(str + i) == *(str + i + 2))
		{
			foundSplit = 1;
			break;
		}
	}
	
	return foundSplit;
}
