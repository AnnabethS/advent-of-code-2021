#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#ifdef DEBUG
#define FILENAME "test.txt"
#define BUFLEN 23
#define CRABAMOUNT 10
#else
#define FILENAME "input.txt"
#define BUFLEN 3924
#define CRABAMOUNT 1000
#endif

int getMean(int crabs[CRABAMOUNT])
{
	float total = 0;

	for(int i=0; i < CRABAMOUNT; i++)
	{
		total += crabs[i];
	}
	total /= (float)CRABAMOUNT;
	printf("mean: %f\n", total);

	return round(total);
}

int main()
{
	FILE* fp;
	fp = fopen(FILENAME, "r");

	char bufStr[BUFLEN];

	fscanf(fp, "%s", bufStr);
	fclose(fp);

	char* nextNum = strtok(bufStr, ",");

	int crabs[CRABAMOUNT];

	int count = 0;

	while (nextNum != NULL)
	{
		crabs[count] = strtol(nextNum, NULL, 10);
		count++;
		nextNum = strtok(NULL, ",");
	}

	int mean = getMean(crabs);
	printf("mean: %d\n", mean);

	int total = 0;

	for (int i=0; i < CRABAMOUNT; i++)
	{
		int dist = abs(mean - crabs[i]);
		total += (dist * (dist+1)) / 2;
	}

	printf("Total Fuel: %d\n", total);

	printf("or\n");

	mean--;
	printf("mean: %d\n", mean);

	total = 0;

	for (int i=0; i < CRABAMOUNT; i++)
	{
		int dist = abs(mean - crabs[i]);
		total += (dist * (dist+1)) / 2;
	}

	printf("Total Fuel: %d\n", total);
}
