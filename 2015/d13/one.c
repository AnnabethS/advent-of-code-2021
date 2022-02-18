#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFLEN 100
#define PEOPLE 8

FILE* fp;
int value[PEOPLE][PEOPLE] = {0};

char parseLine();

int main()
{
	fp = fopen("input.txt", "r");
	while(parseLine());
	printf("------------------------------------------------\n");
	for(int i=0; i < PEOPLE; i++)
	{
		printf("|");
		for(int j=0; j < PEOPLE; j++)
		{
			printf("%3d | ", value[i][j]);
		}
		printf("\n------------------------------------------------\n");
	}
}

int getBestSeating(char picked[PEOPLE], int pick)
{

}

char parseLine()
{
	char bufStr[BUFLEN] = {0};
	char eofcheck = fscanf(fp, "%s", bufStr);
	if (eofcheck == EOF)
		return 0;

	int p1, p2;
	if(bufStr[0] >= 'A' && bufStr[0] <= 'G')
	{
		p1 = bufStr[0] - 'A';
	}
	else
	{
		p1 = 7;
	}
	fscanf(fp, "%s", bufStr);
	int sign = 0;
	fscanf(fp, "%s", bufStr);
	if(bufStr[0]=='g')
		sign = 1;
	else
		sign = -1;
	fscanf(fp, "%s", bufStr);

	int x = strtol(bufStr, NULL, 10);
	x *= sign;
	fscanf(fp, "%s", bufStr);
	fscanf(fp, "%s", bufStr);
	fscanf(fp, "%s", bufStr);
	fscanf(fp, "%s", bufStr);
	fscanf(fp, "%s", bufStr);
	fscanf(fp, "%s", bufStr);
	fscanf(fp, "%s", bufStr);

	// we are now looking at the 2nd name
	if(bufStr[0] >= 'A' && bufStr[0] <= 'G')
	{
		p2 = bufStr[0] - 'A';
	}
	else
	{
		p2 = 7;
	}
	value[p1][p2] = x;
	return 1;
}
