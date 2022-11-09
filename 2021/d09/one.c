#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef DEBUG
#define FILENAME "test.txt"
#define WIDTH 10
#define HEIGHT 5
#else
#define FILENAME "input.txt"
#define WIDTH 100
#define HEIGHT 100
#endif

void printGrid(char grid[HEIGHT][WIDTH+1]);

char isLowPoint(char grid[HEIGHT][WIDTH+1], int x, int y);

int main()
{
	FILE* fp = fopen(FILENAME, "r");

	char grid[HEIGHT][WIDTH+1]= {'0'};

	for(int i=0; i < HEIGHT; i++)
		fscanf(fp, "%s", grid[i]);


	int totalRisk = 0;
	for(int y=0; y < HEIGHT; y++)
	{
		for(int x=0; x < WIDTH; x++)
		{
			if(isLowPoint(grid, x, y))
			{
				switch(grid[y][x])
				{
				case('0'):
					totalRisk += 1;
					break;
				case('1'):
					totalRisk += 2;
					break;
				case('2'):
					totalRisk += 3;
					break;
				case('3'):
					totalRisk += 4;
					break;
				case('4'):
					totalRisk += 5;
					break;
				case('5'):
					totalRisk += 6;
					break;
				case('6'):
					totalRisk += 7;
					break;
				case('7'):
					totalRisk += 8;
					break;
				case('8'):
					totalRisk += 9;
					break;
				case('9'):
					totalRisk += 10;
					break;
				}
			}
		}
	}

	printf("total %d\n", totalRisk);
}

void printGrid(char grid[HEIGHT][WIDTH+1])
{
	for(int i=0; i < HEIGHT; i++)
	{
		printf("%s\n", grid[i]);
	}
}

char isLowPoint(char grid[HEIGHT][WIDTH+1], int x, int y)
{
	if((x+1) < WIDTH)
	{
		if(grid[y][x+1] <= grid[y][x])
			return 0;
	}
	if((x-1) >= 0)
	{
		if(grid[y][x-1] <= grid[y][x])
			return 0;
	}
	if((y+1) < HEIGHT)
	{
		if(grid[y+1][x] <= grid[y][x])
			return 0;
	}
	if((y-1) >= 0)
	{
		if(grid[y-1][x] <= grid[y][x])
			return 0;
	}

	return 1;
}
