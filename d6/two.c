#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef DEBUG
#define FILENAME "test.txt"
#define BUFLENGTH 11
#define STARTFISH 5
#else
#define FILENAME "input.txt"
#define BUFLENGTH 1000
#endif

void printFish(long long fish[9])
{
	for(int i=0; i < 9; i++)
	{
		printf("%d: %lld\n", i, fish[i]);
	}
	printf("-------------------\n\n");
}

void tick(long long fish[9])
{
	long long day0Fish = fish[0]; 
	for (int i=0; i<8; i++)
	{
		fish[i] = fish[i+1];
	}
	fish[8] = 0;
	fish[6] += day0Fish;
	fish[8] += day0Fish;

}

int main()
{
	FILE* fp;
	fp = fopen(FILENAME, "r");

	char buf[BUFLENGTH];
	fscanf(fp, "%s", buf);
	fclose(fp);

	long long fish[9];
	for(int i=0; i < 9; i++)
	{
		fish[i] = 0;
	}
	
	char* nextNum = strtok(buf, ",");
	while (nextNum != NULL)
	{
		fish[strtol(nextNum, NULL, 10)]++;
		nextNum = strtok(NULL, ",");
	}
	for(int i=0; i < 256; i++)
	{
		tick(fish);
	}
	long long total = 0;
	for(int i=0; i < 9; i++)
	{
		total += fish[i];
	}
	printf("%lld\n", total);
}
