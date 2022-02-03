#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FULL

#ifdef FULL
#define CALLNUMAMOUNT 100
#define BINGOGRIDS 100
#define BINGODIMENSIONS 5
#define FILENAME "input.txt"
#endif

#ifdef TEST
#define CALLNUMAMOUNT 27
#define BINGOGRIDS 3
#define BINGODIMENSIONS 5
#define FILENAME "testinput.txt"
#endif
void fillNum(int grid[BINGODIMENSIONS][BINGODIMENSIONS], int num);

char isWinning(const int grid[BINGODIMENSIONS][BINGODIMENSIONS]);

int gridScore(int grid[BINGODIMENSIONS][BINGODIMENSIONS]);

void printGrid(int grid[BINGODIMENSIONS][BINGODIMENSIONS]);

int main()
{
	FILE* fp;
	fp = fopen(FILENAME, "r");

	int callNums[CALLNUMAMOUNT];

	{ // read vals into callNums array
		char callNumsStr[500];
		char* nextNum;
		fscanf(fp, "%s,", callNumsStr);
		int count = 0;

		/* printf("%s\n", callNumsStr); */
		nextNum = strtok(callNumsStr, ",");

		while (nextNum != NULL)
		{
			callNums[count] = strtol(nextNum, NULL, 10);
			count++;
			nextNum = strtok(NULL, ",");
		}
	}

	// read in grids
	int bingoGrids[BINGOGRIDS][BINGODIMENSIONS][BINGODIMENSIONS];

	{
		char eofreached;
		char bufStr[3];
		eofreached = fscanf(fp, "%s", bufStr);
		int gridNum = 0;
		int gridX = 0;
		int gridY = 0;

		while(eofreached != EOF)
		{
			bingoGrids[gridNum][gridX][gridY] = strtol(bufStr, NULL, 10);
			gridX++;
			if(gridX >= BINGODIMENSIONS)
			{
				gridX = 0;
				gridY++;
			}
			if(gridY >= BINGODIMENSIONS)
			{
				gridY = 0;
				gridNum++;
			}
			eofreached = fscanf(fp, "%s", bufStr);
		}
	}

	fclose(fp);

	int winningGridNum = -1;
	int winningNumber = 0;
	int lastGridEliminated = -1;
	char gridEliminated[BINGOGRIDS];

	for(int i=0; i < BINGOGRIDS; i++)
	{
		gridEliminated[i] = 0;
	}

	for(int i=0; i < CALLNUMAMOUNT; i++)
	{
		printGrid(bingoGrids[44]);
		printf("\n");
		for(int grid=0; grid < BINGOGRIDS; grid++)
		{
			fillNum((bingoGrids[grid]), callNums[i]);
		}
		for(int grid=0; grid < BINGOGRIDS; grid++)
		{
			if(isWinning(bingoGrids[grid]))
			{
				gridEliminated[grid] = 1;
			}
			if(grid==44)
			{
				printf("%d\n", isWinning(bingoGrids[44]));
			}
		}

		int gridsLeft = 0;
		for(int grid=0; grid < BINGOGRIDS; grid++)
		{
			if(gridEliminated[grid] == 0)
				gridsLeft++;
		}

		if(gridsLeft <= 1)
		{
			for(int grid=0; grid < BINGOGRIDS; grid++)
			{
				if(!gridEliminated[grid])
					winningGridNum = grid;
			}	
			/* printf("%d\n", callNums[i]); */
			/* printGrid(bingoGrids[winningGridNum]); */
			/* printf("\n"); */
			if(isWinning(bingoGrids[winningGridNum]))
			{
				printf("yo\n");
				winningNumber = callNums[i];
				break;
			}
			
		}
	}

	printf("testtesttest\n");
	printGrid(bingoGrids[winningGridNum]);
	printf("\n");
	fillNum(bingoGrids[winningGridNum], winningNumber);
	printGrid(bingoGrids[winningGridNum]);
	printf("is winning : %d", isWinning(bingoGrids[winningGridNum]));
	int finalScore = gridScore(bingoGrids[winningGridNum]) * winningNumber;
	printf("winning num: %d | winning grid num: %d\n", winningNumber, winningGridNum);

	printf("final score: %d\n", finalScore);
}

void fillNum(int grid[BINGODIMENSIONS][BINGODIMENSIONS], int num)
{
	for (int i=0; i < BINGODIMENSIONS; i++)
	{
		for (int j=0; j < BINGODIMENSIONS; j++)
		{
			if(grid[i][j]==num)
				grid[i][j] = -1;
		}
	}
}

char isWinning(const int grid[BINGODIMENSIONS][BINGODIMENSIONS])
{
	//check rows
	for (int row=0; row < BINGODIMENSIONS; row++)
	{
		char winRow = 1;
		for(int col=0; col < BINGODIMENSIONS; col++)
		{
			if(grid[col][row] != -1)
			{
				winRow = 0;
				break;
			}
		}
		if (winRow)
		{
			return 1;
		}
	}

	//check columns
	for (int col=0; col < BINGODIMENSIONS; col++)
	{
		char winCol = 1;
		for (int row=0; row < BINGODIMENSIONS; row++)
		{
			if(grid[col][row] != -1)
			{
				winCol = 0;
			}
		}
		if (winCol)
		{
			return 1;
		}
	}

	//not winning
	return 0;
}

int gridScore(int grid[BINGODIMENSIONS][BINGODIMENSIONS])
{
	int total = 0;
	for(int i=0; i < BINGODIMENSIONS; i++)
	{
		for(int j=0; j < BINGODIMENSIONS; j++)
		{
			if(grid[i][j] != -1)
			{
				total += grid[i][j];
			}
		}
	}
	return total;
}

void printGrid(int grid[BINGODIMENSIONS][BINGODIMENSIONS])
{
	for(int i=0; i < BINGODIMENSIONS; i++)
	{
		for(int j=0; j < BINGODIMENSIONS; j++)
		{
			if(grid[j][i] < 10 && grid[j][i] != -1)
				printf(" ");
			printf("%d ", grid[j][i]);
		}
		printf("\n");
	}
}
