#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


#ifdef TEST
#define dims 10
#define FILENAME "test.txt"
#define maxNumLen 1
#define linesNum 10
#else
#define dims 1000
#define FILENAME "input.txt"
#define maxNumLen 3
#define linesNum 500
#endif

typedef struct vec2{
	int x;
	int y;
} vec2;

typedef struct line{
	vec2 start;
	vec2 end;
} line;

void printLine(line* l);

void fillLine(int grid[dims][dims], line* l);

void printGrid(int grid[dims][dims]);

int main()
{
	FILE* fp;
	fp = fopen(FILENAME, "r");

	char bufStr1[(maxNumLen*2)+2];
	char bufStr2[(maxNumLen*2)+2];
	char eofreached;
	char* nextNum;
	line lines[linesNum];
	int count = 0;

	eofreached = fscanf(fp, "%s -> %s", bufStr1, bufStr2);

	while(eofreached != EOF)
	{
		// start loc
		nextNum = strtok(bufStr1, ",");
		lines[count].start.x = strtol(nextNum, NULL, 10);
		nextNum = strtok(NULL, ",");
		lines[count].start.y = strtol(nextNum, NULL, 10);

		// end loc
		nextNum = strtok(bufStr2, ",");
		lines[count].end.x = strtol(nextNum, NULL, 10);
		nextNum = strtok(NULL, ",");
		lines[count].end.y = strtol(nextNum, NULL, 10);
		eofreached = fscanf(fp, "%s -> %s", bufStr1, bufStr2);
		count++;
	}
	for (int i=0; i < count; i++)
	{
		if(lines[i].start.x > lines[i].end.x && lines[i].start.y == lines[i].end.y)
		{
			int buf = lines[i].end.x;
			lines[i].end.x = lines[i].start.x;
			lines[i].start.x = buf;
		}
		if(lines[i].start.y > lines[i].end.y && lines[i].start.x == lines[i].end.x)
		{
			int buf = lines[i].end.y;
			lines[i].end.y = lines[i].start.y;
			lines[i].start.y = buf;
		}
	}
	fclose(fp);
	int grid[dims][dims];
	for(int x=0; x < dims; x++)
	{
		for(int y=0; y < dims; y++)
		{
			grid[y][x] = 0;
		}
	}
	for(int i=0; i < count; i++)
	{
		/* printLine(&lines[i]); */
		fillLine(grid, &lines[i]);
	}
	int overlaps = 0;
	for(int x=0; x < dims; x++)
	{
		for(int y=0; y < dims; y++)
		{
			if(grid[x][y] >= 2)
				overlaps++;
		}
	}
	printf("overlaps: %d\n", overlaps);	
}

void printLine(line* l)
{
	printf("%d,%d -> %d,%d\n",l->start.x, l->start.y, l->end.x, l->end.y);
}

void fillLine(int grid[dims][dims], line* l)
{
	if(l->start.x == l->end.x)
	{
		for(int y=l->start.y; y <= l->end.y; y++)
		{
			grid[y][l->start.x]++;
			/* printf("%d,%d ", l->start.x, y); */
		}
	}
	else if (l->start.y == l->end.y)
	{
		for(int x=l->start.x; x <= l->end.x; x++)
		{
			grid[l->start.y][x]++;
			/* printf("%d,%d ", x, l->start.y); */
		}
	}
	else
	{
		int length = abs(l->end.x - l->start.x);
		int deltaX = 1;
		int deltaY = 1;

		if(l->end.x < l->start.x)
			deltaX = -1;

		if(l->end.y < l->start.y)
			deltaY = -1;

		for(int i=0; i <= length; i++)
		{
			grid[l->start.y + (i*deltaY)][l->start.x + (i*deltaX)]++;
		}
	}
	/* printf("\n"); */
	return;
}

void printGrid(int grid[dims][dims])
{
	for(int x=0; x < dims; x++)
	{
		for(int y=0; y < dims; y++)
		{
			printf("%d ", grid[x][y]);
		}
		printf("\n");
	}
}
