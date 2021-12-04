#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CALLNUMAMOUNT 250
#define BINGOGRIDS 100
#define BINGODIMENSIONS 5

void fillNum(int grid[BINGODIMENSIONS][BINGODIMENSIONS], int num);

char isWinning(int grid[BINGODIMENSIONS][BINGODIMENSIONS]);

int gridScore(int grid[BINGODIMENSIONS][BINGODIMENSIONS]);

int main()
{
	FILE* fp;
	fp = fopen("input.txt", "r");

	int callNums[CALLNUMAMOUNT];

	{ // read vals into callNums array
		char callNumsStr[300];
		char* nextNum;
		fscanf(fp, "%s,", callNumsStr);
		int count = 0;

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

	for(int i=0; i < CALLNUMAMOUNT; i++)
	{
		for(int grid=0; grid < BINGOGRIDS; grid++)
		{
			fillNum((bingoGrids[grid]), callNums[i]);
		}
		for(int grid=0; grid < BINGOGRIDS; grid++)
		{
			if(isWinning(bingoGrids[grid]))
			{
				printf("iteration: %d\n", i);
				winningGridNum = grid;
				winningNumber = callNums[i];
				break;
			}
		}
		if(winningGridNum != -1)
			break;
	}

	int finalScore = gridScore(bingoGrids[winningGridNum]) * winningNumber;
	printf("winning num: %d | winning grid num: %d\n", winningNumber, winningGridNum);

	printf("final score: %d\n", finalScore);
}

void fillNum(int grid[BINGODIMENSIONS][BINGODIMENSIONS], int num)
{
	for (int i=0; i < BINGOGRIDS; i++)
	{
		for (int j=0; j < BINGOGRIDS; j++)
		{
			if(grid[i][j]==num)
				grid[i][j] = -1;
		}
	}
}

char isWinning(int grid[BINGODIMENSIONS][BINGODIMENSIONS])
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
