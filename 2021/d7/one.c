#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifdef DEBUG
#define FILENAME "test.txt"
#define BUFLEN 23
#define CRABAMOUNT 10
#else
#define FILENAME "input.txt"
#define BUFLEN 3924
#define CRABAMOUNT 1000
#endif

int cmp(const void* a, const void* b)
{
	return (*(int*)a > *(int*)b);
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

	/* for (int i=0; i < CRABAMOUNT; i++) */
	/* { */
	/* 	printf("%d ", crabs[i]); */
	/* } */
	/* printf("\n"); */

	printf("last crab: %d\n", crabs[CRABAMOUNT-1]);

	qsort(crabs, CRABAMOUNT, sizeof(int), cmp);

	/* for (int i=0; i < CRABAMOUNT; i++) */
	/* { */
	/* 	printf("%d ", crabs[i]); */
	/* } */
	/* printf("\n"); */
	
	int median = crabs[(CRABAMOUNT + 1) / 2];
	printf("median: %d\n", median);

	int total = 0;

	for (int i=0; i < CRABAMOUNT; i++)
	{
		total += abs(median - crabs[i]);
	}

	printf("Total Fuel: %d\n", total);
}
