#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef DEBUG
#define FILENAME "test.txt"
#define WIDTH 10
#define HEIGHT 5
#define BASINAMOUNT 4
#else
#define FILENAME "input.txt"
#define WIDTH 100
#define HEIGHT 100
#define BASINAMOUNT 253
#endif

typedef struct v2l{
	int x;
	int y;
	struct v2l* next;
}v2l;

void printGrid(char grid[HEIGHT][WIDTH+1]);

char isLowPoint(char grid[HEIGHT][WIDTH+1], int x, int y);

int getBasinSize(char grid[HEIGHT][WIDTH+1], int x, int y);

void expandCell(char grid[HEIGHT][WIDTH+1], int x, int y, char results[4]);

int main()
{
	FILE* fp = fopen(FILENAME, "r");

	char grid[HEIGHT][WIDTH+1]= {'0'};

	for(int i=0; i < HEIGHT; i++)
		fscanf(fp, "%s", grid[i]);


	int basinAmount = 0;
	char basinLocations[BASINAMOUNT][2];
	for(int y=0; y < HEIGHT; y++)
	{
		for(int x=0; x < WIDTH; x++)
		{
			if(isLowPoint(grid, x, y))
			{
				basinLocations[basinAmount][0] = x;
				basinLocations[basinAmount][1] = y;
				basinAmount++;
			}
		}
	}

	printf("basins: %d\n", basinAmount);

	int topBasinSizes[3] = {-1};
	int currBasinSize = 0;

	for (int i=0; i < BASINAMOUNT; i++)
	{
		currBasinSize = getBasinSize(grid, basinLocations[i][0], basinLocations[i][1]);
		if(currBasinSize >= topBasinSizes[0])
		{
			topBasinSizes[2] = topBasinSizes[1];
			topBasinSizes[1] = topBasinSizes[0];
			topBasinSizes[0] = currBasinSize;
		}
		else if(currBasinSize >= topBasinSizes[1])
		{
			topBasinSizes[2] = topBasinSizes[1];
			topBasinSizes[1] = currBasinSize;
		}
		else if(currBasinSize > topBasinSizes[2])
			topBasinSizes[2] = currBasinSize;
	}

	printf("%d %d %d\n", topBasinSizes[0], topBasinSizes[1], topBasinSizes[2]);

	printf("final out: %d\n", (topBasinSizes[0]*topBasinSizes[1]*topBasinSizes[2]));
}

int getBasinSize(char grid[HEIGHT][WIDTH+1], int x, int y)
{
	int size = 1;
	v2l* queueHead = (v2l*) malloc(sizeof(v2l));
	v2l* queueTail = queueHead;

	printf("BASIN AT %d %d\n", x, y);

	grid[y][x] = 'X';

	queueHead->x = x;
	queueTail->y = y;

	char results[4] = {'0'};
	expandCell(grid, queueHead->x, queueHead->y, results);

	printf("%d %d\n", queueHead->x, queueHead->y);

	if(results[0])
	{
		grid[queueHead->y][queueHead->x+1] = 'X';
		size++;
		queueTail->next = (v2l*) malloc(sizeof(v2l));
		queueTail = queueTail->next;
		queueTail->next = NULL;
		queueTail->x = queueHead->x + 1;
		queueTail->y = queueHead->y;
	}
	if(results[1])
	{
		grid[queueHead->y][queueHead->x-1] = 'X';
		size++;
		queueTail->next = (v2l*) malloc(sizeof(v2l));
		queueTail = queueTail->next;
		queueTail->next = NULL;
		queueTail->x = queueHead->x - 1;
		queueTail->y = queueHead->y;
	}
	if(results[2])
	{
		grid[queueHead->y+1][queueHead->x] = 'X';
		size++;
		queueTail->next = (v2l*) malloc(sizeof(v2l));
		queueTail = queueTail->next;
		queueTail->next = NULL;
		queueTail->x = queueHead->x;
		queueTail->y = queueHead->y + 1;
	}
	if(results[3])
	{
		grid[queueHead->y-1][queueHead->x] = 'X';
		size++;
		queueTail->next = (v2l*) malloc(sizeof(v2l));
		queueTail = queueTail->next;
		queueTail->next = NULL;
		queueTail->x = queueHead->x;
		queueTail->y = queueHead->y - 1;
	}
	v2l* oldHead = queueHead;
	queueHead = queueHead->next;
	free(oldHead);

	while(queueHead != NULL)
	{
		printf("%d %d\n", queueHead->x, queueHead->y);
		expandCell(grid, queueHead->x, queueHead->y, results);

		if(results[0])
		{
			grid[queueHead->y][queueHead->x+1] = 'X';
			size++;
			queueTail->next = (v2l*) malloc(sizeof(v2l));
			queueTail = queueTail->next;
			queueTail->next = NULL;
			queueTail->x = queueHead->x + 1;
			queueTail->y = queueHead->y;
		}
		if(results[1])
		{
			grid[queueHead->y][queueHead->x-1] = 'X';
			size++;
			queueTail->next = (v2l*) malloc(sizeof(v2l));
			queueTail = queueTail->next;
			queueTail->next = NULL;
			queueTail->x = queueHead->x - 1;
			queueTail->y = queueHead->y;
		}
		if(results[2])
		{
			grid[queueHead->y+1][queueHead->x] = 'X';
			size++;
			queueTail->next = (v2l*) malloc(sizeof(v2l));
			queueTail = queueTail->next;
			queueTail->next = NULL;
			queueTail->x = queueHead->x;
			queueTail->y = queueHead->y + 1;
		}
		if(results[3])
		{
			grid[queueHead->y-1][queueHead->x] = 'X';
			size++;
			queueTail->next = (v2l*) malloc(sizeof(v2l));
			queueTail = queueTail->next;
			queueTail->next = NULL;
			queueTail->x = queueHead->x;
			queueTail->y = queueHead->y - 1;
		}
		v2l* oldHead = queueHead;
		queueHead = queueHead->next;
		free(oldHead);
	}

	return size;
}

void printGrid(char grid[HEIGHT][WIDTH+1])
{
	for(int i=0; i < HEIGHT; i++)
	{
		printf("%s\n", grid[i]);
	}
}

void expandCell(char grid[HEIGHT][WIDTH+1], int x, int y, char results[4])
{
	if((x+1) < WIDTH)
	{
		if(grid[y][x+1] != '9' && grid[y][x+1]!='X')
		{
			results[0] = 1;
		}
		else
			results[0] = 0;
	}
	else
		results[0] = 0;

	if((x-1) >= 0)
	{
		if(grid[y][x-1] != '9' && grid[y][x-1]!='X')
		{
			results[1] = 1;
		}
		else
			results[1] = 0;
	}
	else
		results[1] = 0;

	if((y+1) < HEIGHT)
	{
		if(grid[y+1][x] != '9' && grid[y+1][x]!='X')
		{
			results[2] = 1;
		}
		else
			results[2] = 0;
	}
	else
		results[2] = 0;

	if((y-1) >= 0)
	{
		if(grid[y-1][x] != '9' && grid[y-1][x]!='X')
		{
			results[3] = 1;
		}
		else
			results[3] = 0;
	}	
	else
		results[3] = 0;
}

char isLowPoint(char grid[HEIGHT][WIDTH+1], int x, int y)
{
	if(grid[y][x]=='X')
		return 0;
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
