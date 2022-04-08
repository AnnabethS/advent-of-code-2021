#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define BUFLEN 100
#define PEOPLE 9

FILE* fp;
int value[PEOPLE][PEOPLE] = {0};

char parseLine();
char nextPermutation(char picked[PEOPLE]);
char isValidPermutation(char picked[PEOPLE]);
int getSeatingValue(char picked[PEOPLE]);

int main()
{
	fp = fopen("input.txt", "r");
	while(parseLine());
	printf("    ");
	for(int i=0; i < PEOPLE; i++)
	{
		printf("%4d |", i);
	}
	printf("\n   ---------------------------------------------\n");
	for(int i=0; i < PEOPLE; i++)
	{
		printf("%3d |", i);
		for(int j=0; j < PEOPLE; j++)
		{
			printf("%3d | ", value[i][j]);
		}
		printf("\n   ---------------------------------------------\n");
	}
	char picked[PEOPLE] = {0};
	// 0 0 0 0 0 0 0 0
	// we can increment the leftmost elem [0] and then check if its valid, if yes
	// calculate the seating happiness
	// then keep incrementing, when an elem passes 9, increase the one to left and
	// set all ones to the right to 0
	char run = 1;
	int best = INT_MIN;
	char bestSeats[PEOPLE+1];
	while(run)
	{
		// check if the arrangement is valid
		char check = isValidPermutation(picked);

		// if yes then calculate and set equal to best if its more than current best
		if(check)
		{
			int current = getSeatingValue(picked);
			if(current > best)
				best = current;
			memcpy(bestSeats, picked, sizeof(char)*PEOPLE);
			/* break; */
		}


		// next permutation
		run = nextPermutation(picked);
	}
	printf("best: %d\n", best);
	for(int i=0; i < PEOPLE; i++)
		printf("%d ", bestSeats[i]);
	printf("\n");
}

int getSeatingValue(char picked[PEOPLE])
{
	int total = 0;
	total += value[picked[PEOPLE-1]][picked[0]];
	total += value[picked[0]][picked[PEOPLE-1]];
	/* printf("%d + %d + ", value[picked[7]][picked[0]], value[picked[0]][picked[7]]); */
	for(int i=0; i < PEOPLE-1; i++)
	{
		total += value[picked[i]][picked[i+1]];
		total += value[picked[i+1]][picked[i]];
		/* printf("%d + %d + ", value[picked[i]][picked[i+1]], */
							/* value[picked[i+1]][picked[i]]); */
	}
	/* printf("\n"); */
	return total;
}

char isValidPermutation(char picked[PEOPLE])
{
	for(int i=0; i < PEOPLE; i++)
	{
		for(int j=0; j < PEOPLE; j++)
		{
			if(j != i && picked[i]==picked[j])
				return 0;
		}
	}
	return 1;
}

char nextPermutation(char picked[PEOPLE])
{
	for(int i=0; i < PEOPLE; i++)
	{
		picked[i]++;
		if(picked[i] < PEOPLE)
			return 1;
		if(i == PEOPLE-1)
			return 0;
		// we must bubble up
		for(int j=i; j >= 0; j--)
		{
			picked[j] = 0;
		}
	}
	printf("unreachable\n");
	return 0;
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
