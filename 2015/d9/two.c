#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

#define NODES 8
// test is defined LONDON, DUBLIN, BELFAST
/* int distances[NODES][NODES] = { */
/*     {0, 464, 518}, */
/*     {518, 0, 141}, */
/*     {464, 141, 0}}; */

int distances[NODES][NODES] = {0};

FILE* fp;

int getLocationNum(char* str);
int getHighestDistance(int start, char visited[NODES]);
char parseLine();

int main()
{
	fp = fopen("input.txt", "r");
	char visited[NODES] = {0};
	while(parseLine());
	int high = INT_MIN;
	for(int i=0; i < NODES; i++)
	{
		/* printf("starting_at_node: %d\n", i); */
		char newVisited[NODES];
		memcpy(&newVisited, visited, sizeof(char)*NODES);
		newVisited[i] = 1;
		int tmp = getHighestDistance(i, newVisited);
		if(tmp > high)
			high = tmp;
	}
	printf("%d\n", high);
}

char parseLine()
{
	char bufStr[20];
	char eofcheck = fscanf(fp, "%s", bufStr);
	if(eofcheck == EOF)
		return 0;
	int locStart, locEnd;
	locStart = getLocationNum(bufStr);
	fscanf(fp, "%s", bufStr);
	fscanf(fp, "%s", bufStr);
	locEnd = getLocationNum(bufStr);
	fscanf(fp, "%s", bufStr);
	fscanf(fp, "%s", bufStr);
	int cost = strtol(bufStr, NULL, 10);
	distances[locStart][locEnd] = cost;
	distances[locEnd][locStart] = cost;
	printf("%d -> %d = %d\n", locStart, locEnd, cost);
	return 1;
}

int getHighestDistance(int start, char visited[NODES])
{
	int currentHigh = INT_MIN;
	char check = 0;
	for(int i=0; i < NODES; i++)
	{
		if(!visited[i])
			check = 1;
	}
	if(!check)
		return 0;
	for(int i=0; i < NODES; i++)
	{
		if(!visited[i] && start != i)
		{
			char newVisited[NODES];
			memcpy(&newVisited, visited, sizeof(char)*NODES);
			newVisited[i] = 1;
			/* printf("now checking %d -> %d\n", start, i); */
			int high = distances[start][i] + getHighestDistance(i, newVisited);
			if(currentHigh < high)
			{
				currentHigh = high;
			}
		}
	}
	return currentHigh;
}

int getLocationNum(char* str)
{
	if(strcmp(str, "AlphaCentauri") == 0)
	{
		return 0;
	}
	else if(strcmp(str, "Snowdin") == 0)
	{
		return 1;
	}
	else if(strcmp(str, "Tambi") == 0)
	{
		return 2;
	}
	else if(strcmp(str, "Faerun") == 0)
	{
		return 3;
	}
	else if(strcmp(str, "Norrath") == 0)
	{
		return 4;
	}
	else if(strcmp(str, "Straylight") == 0)
	{
		return 5;
	}
	else if(strcmp(str, "Tristram") == 0)
	{
		return 6;
	}
	else if(strcmp(str, "Arbre") == 0)
	{
		return 7;
	}
	else
	{
		printf("UNREACHABLE: defaulting to AlphaCentauri\n");
		return 0;
	}
}
