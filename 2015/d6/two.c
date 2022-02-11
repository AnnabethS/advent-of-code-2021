#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRSIZE 1000

void toggleSquare(int startX, int startY, int endX, int endY);
void setSquare(int startX, int startY, int endX, int endY, char value);
char parseLine();

enum operation{
	OFF, ON, TOGGLE
};

char lights[1000][1000] = {0};
FILE* fp;

int main()
{
	fp = fopen("input.txt", "r");
	char run = 1;
	while(run)
	{
		run = parseLine();
	}
	int lightsOn = 0;
	for(int i=0; i < ARRSIZE; i++)
	{
		for(int j=0; j < ARRSIZE; j++)
		{
			lightsOn += lights[i][j];
		}
	}
	printf("lights on: %d\n", lightsOn);
}

char parseLine()
{
	enum operation doFunc;
	int startX, startY, endX, endY;
	char bufStr[16] = {0};
	char eofcheck = fscanf(fp, "%s", bufStr);
	if(eofcheck == EOF)
		return 0;
	if(bufStr[1] == 'o')
	{
		doFunc = TOGGLE;
	}
	else
	{
		fscanf(fp, "%s", bufStr);
		if(bufStr[1] == 'f')
			doFunc = OFF;
		else
			doFunc = ON;
	}
	fscanf(fp, "%s", bufStr);
	char* coordinatePtr = strtok(bufStr, ",");
	startX = strtol(coordinatePtr, NULL, 10);
	coordinatePtr = strtok(NULL, ",");
	startY = strtol(coordinatePtr, NULL, 10);
	fscanf(fp, "%s", bufStr);
	fscanf(fp, "%s", bufStr);
	coordinatePtr = strtok(bufStr, ",");
	endX = strtol(coordinatePtr, NULL, 10);
	coordinatePtr = strtok(NULL, ",");
	endY = strtol(coordinatePtr, NULL, 10);
	switch(doFunc)
	{
	case(ON):
		setSquare(startX, startY, endX, endY, 1);
		break;
	case(OFF):
		setSquare(startX, startY, endX, endY, 0);
		break;
	case(TOGGLE):
		toggleSquare(startX, startY, endX, endY);
		break;
	}
	return 1;
}

void setSquare(int startX, int startY, int endX, int endY, char value)
{
	for(int row=startY; row <= endY; row++)
	{
		memset(&lights[row][startX], (int)value, sizeof(char)*((endX-startX) + 1));
	}
}

void toggleSquare(int startX, int startY, int endX, int endY)
{
	for(int i=startY; i <= endY; i++)
	{
		for(int j=startX; j <= endX; j++)
		{
			lights[i][j] = !lights[i][j];
		}
	}
}
