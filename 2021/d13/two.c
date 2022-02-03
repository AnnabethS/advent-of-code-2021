#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#ifdef TEST
#define FILENAME "test.txt"
#define DOTAMOUNT 18
#define BUFLENGTH 16
#define FOLDAMOUNT 2
#else
#define FILENAME "input.txt"
#define DOTAMOUNT 916
#define BUFLENGTH 18
#define FOLDAMOUNT 12
#endif

typedef struct v2{
	int x;
	int y;
}v2;

typedef struct fold{
	char dir;
	int n;
}fold;

// debug printing funcs

void printDot(const v2 *dot);
void printDotList(const v2 dots[DOTAMOUNT]);
void printDotGrid(const v2 dots[DOTAMOUNT], const int maxX, const int maxY);

void printFold(const fold *f);
void printFoldList(const fold f[FOLDAMOUNT]);

// actual logic funcs

void doFold(v2 dots[DOTAMOUNT], const fold f, int *maxX, int *maxY);

int main()
{
	FILE* fp = fopen(FILENAME, "r");
	char bufStr[BUFLENGTH] = {'\0'};
	v2 dots[DOTAMOUNT];
	for(int i=0; i < DOTAMOUNT; i++)
	{
		fscanf(fp, "%s", bufStr);
		dots[i].x = strtol(strtok(bufStr, ","), NULL, 10);
		dots[i].y = strtol(strtok(NULL, ","), NULL, 10);
	}
	fold folds[FOLDAMOUNT];

	for(int i=0; i < FOLDAMOUNT; i++)
	{
		fscanf(fp, "%s", bufStr);
		fscanf(fp, "%s", bufStr);
		fscanf(fp, "%s", bufStr);
		folds[i].dir = bufStr[0];
		strtok(bufStr, "=");
		folds[i].n = strtol(strtok(NULL, "="), NULL, 10);
	}

	int maxX;
	int maxY;

	for (int i=0; i < DOTAMOUNT; i++)
	{
		if(dots[i].x>maxX)
			maxX = dots[i].x;
		if(dots[i].y>maxY)
			maxY = dots[i].y;
	}

	/* printDotGrid(dots, maxX, maxY); */
	for(int i=0; i < FOLDAMOUNT; i++)
		doFold(dots, folds[i], &maxX, &maxY);
	/* printf("\n"); */
	/* printDotList(dots); */
	/* printf("\n"); */
	printDotGrid(dots, maxX, maxY);

	int totaldots = 0;
	for(int i=0; i < DOTAMOUNT; i++)
	{
		totaldots += (dots[i].x != INT_MIN);
	}

	printf("total: %d\n", totaldots);
}

void doFold(v2 dots[DOTAMOUNT], const fold f, int *maxX, int *maxY)
{
	for(int i=0; i < DOTAMOUNT; i++)
	{
		if(dots[i].x == INT_MIN) //INT_MIN means this dot got combined
			continue; //therefore we can just evaluate the other one, saving time
		int *relevantCoord;
		if(f.dir == 'x')
		{
			relevantCoord = &dots[i].x;
			*maxX = f.n - 1;
		}
		else
		{
			relevantCoord = &dots[i].y;
			*maxY = f.n - 1;
		}

		if(*relevantCoord < f.n)
			continue;

		*relevantCoord = f.n - (*relevantCoord - f.n);
	}
	for(int i=0; i < DOTAMOUNT; i++)
	{
		for(int j = i+1; j < DOTAMOUNT; j++)
		{
			if(dots[i].x == dots[j].x && dots[i].y == dots[j].y)
			{
				dots[j].x = INT_MIN;
			}
		}
	}
}

void printDot(const v2 *dot)
{
	printf("X: %d, Y: %d\n", dot->x, dot->y);
}

void printDotList(const v2 dots[DOTAMOUNT])
{
	for(int i=0; i < DOTAMOUNT; i++)
	{
		printDot(&dots[i]);
	}
}

void printDotGrid(const v2 dots[DOTAMOUNT], const int maxX, const int maxY)
{
	for(int y=0; y <= maxY; y++)
	{
		for(int x=0; x <= maxX; x++)
		{
			char check = 0;
			for(int i=0; i < DOTAMOUNT; i++)
			{
				if(dots[i].x == x && dots[i].y == y)
					check = 1;
			}
			if(check)
				printf("# ");
			else
				printf(". ");
		}
		printf("\n");
	}
}

void printFold(const fold *f)
{
	printf("Dir: %c, N: %d\n", f->dir, f->n);
}

void printFoldList(const fold f[FOLDAMOUNT])
{
	for(int i=0; i < FOLDAMOUNT; i++)
	{
		printFold(&f[i]);
	}
}
