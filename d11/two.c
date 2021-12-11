#include <stdio.h>
#include <stdlib.h>

#ifdef TEST
#define FILENAME "test.txt"
#define LINELENGTH 10
#define LINES 10
#else
#define FILENAME "input.txt"
#define LINELENGTH 10
#define LINES 10
#endif

void printOctoVals(int octoVal[LINES][LINELENGTH]);

int step(int octoVal[LINES][LINELENGTH]);

void increaseSurroundingOctos(int octoVal[LINES][LINELENGTH], int x, int y);

int main()
{
	FILE* fp = fopen(FILENAME, "r");
	int octoVal[LINES][LINELENGTH];
	char bufStr[LINELENGTH+1];
	char tmp[2];
	tmp[1] = '\0';
	for(int i=0; i < LINES; i++)
	{
		fscanf(fp, "%s\n", bufStr);
		for(int j=0; j < LINELENGTH; j++)
		{
			tmp[0] = bufStr[j];
			octoVal[i][j] = atoi(&tmp[0]);
		}
	}

	int totalflashes = 0;
	int count = 0;
	while(totalflashes != 100)
	{
		count++;
		totalflashes = step(octoVal);
	}

	printf("simultaneous flash at step %d\n", count);
}

int step(int octoVal[LINES][LINELENGTH])
{
	int flashes = 0;
	for(int i=0; i < LINES; i++)
	{
		for(int j=0; j < LINELENGTH; j++)
		{
			octoVal[i][j]++;
		}
	}

	// 1 if on the previous iter through, an octo flashed. also true on iter 1
	char stepFlashed = 1;
	while(stepFlashed)
	{
		stepFlashed = 0;
		for(int y=0; y < LINES; y++)
		{
			for(int x=0; x < LINELENGTH; x++)
			{
				if(octoVal[y][x] > 9)
				{
					flashes++;
					stepFlashed = 1;
					increaseSurroundingOctos(octoVal, x, y);
					octoVal[y][x] = -1;
				}
			}
		}
	}

	// no more steps to be taken
	// change octos that have flashed (they are at -1) back to 0 to be ready
	// for the next time step
	//
	/* printOctoVals(octoVal); */
	/* printf("\n"); */
	
	for(int i=0; i < LINES; i++)
	{
		for(int j=0; j < LINELENGTH; j++)
		{
			if(octoVal[i][j] == -1)
				octoVal[i][j] = 0;
		}
	}

	return flashes;
}

void increaseSurroundingOctos(int octoVal[LINES][LINELENGTH], int x, int y)
{
	char right = x+1 < LINELENGTH;
	char left = x-1 >= 0;
	char up = y-1 >= 0;
	char down = y+1 < LINES;

	if(right)
	{
		if(octoVal[y][x+1] != -1)
			octoVal[y][x+1]++;
		if(up)
			if(octoVal[y-1][x+1] != -1)
				octoVal[y-1][x+1]++;
		if(down)
			if(octoVal[y+1][x+1] != -1)
				octoVal[y+1][x+1]++;
	}
	if(left)
	{
		if(octoVal[y][x-1] != -1)
			octoVal[y][x-1]++;
		if(up)
			if(octoVal[y-1][x-1] != -1)
				octoVal[y-1][x-1]++;
		if(down)
			if(octoVal[y+1][x-1] != -1)
				octoVal[y+1][x-1]++;
	}
	if(up)
		if(octoVal[y-1][x] != -1)
			octoVal[y-1][x]++;
	if(down)
		if(octoVal[y+1][x] != -1)
			octoVal[y+1][x]++;
}

void printOctoVals(int octoVal[LINES][LINELENGTH])
{
	int tmp;
	for (int i=0; i < LINES; i++)
	{
		for(int j=0; j < LINELENGTH; j++)
		{
			tmp = octoVal[i][j];
			printf("%d ", tmp);
		}
		printf("\n");
	}
}
