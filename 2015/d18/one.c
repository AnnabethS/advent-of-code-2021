#include <stdio.h>
#include <string.h>

int getAliveNeighbours(int x, int y);
void updateCell(int x, int y);
char getCellAlive(int x, int y);
void updateGrid();

char frontBuf[100][100] = {0};
char backBuf[100][100] = {0};

int main()
{
	char lineBuffer[101] = {0};
	FILE* fp = fopen("input.txt", "r");
	for(int i=0; i < 100; i++)
	{
		fscanf(fp, "%s", lineBuffer);
		for(int j=0; j < 100; j++)
		{
			frontBuf[i][j] = (lineBuffer[j] == '#');
		}
	}
	fclose(fp);
	for(int i=0; i < 100; i++)
	{
		updateGrid();
	}
	int total = 0;
	for(int i=0; i < 100; i++)
	{
		for(int j=0; j < 100; j++)
		{
			total += frontBuf[i][j];
		}
	}
	printf("lit cells at end: %d\n", total);
}

void updateGrid()
{
	for(int i=0; i < 100; i++)
	{
		for(int j=0; j < 100; j++)
		{
			updateCell(i, j);
		}
	}
	memcpy(frontBuf, backBuf, 100*100*sizeof(char));
}

void updateCell(int x, int y)
{
	if(frontBuf[x][y])
	{ // cell is on
		int neighbours = getAliveNeighbours(x, y);
		if (neighbours == 3 || neighbours == 2)
			backBuf[x][y] = 1;
		else
			backBuf[x][y] = 0;
	}
	else
	{ // cell is off
		int neighbours = getAliveNeighbours(x, y);
		if (neighbours == 3)
			backBuf[x][y] = 1;
		else
			backBuf[x][y] = 0;
	}
}

int getAliveNeighbours(int x, int y)
{
	return (getCellAlive(x-1, y-1) +
		getCellAlive(x, y-1) +
		getCellAlive(x+1, y-1) +
		getCellAlive(x+1, y) +
		getCellAlive(x+1, y+1) +
		getCellAlive(x, y+1) +
		getCellAlive(x-1, y+1) +
		getCellAlive(x-1, y));
}

char getCellAlive(int x, int y)
{
	if(x < 0 || x >= 100 || y < 0 || y >= 100)
		return 0;
	else
		return frontBuf[x][y];
}
