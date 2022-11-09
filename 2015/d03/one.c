#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct house_l{
	int x;
	int y;
	struct house_l* next;
}house_l;

house_l* houseListHead = NULL;

house_l* initHouse(int x, int y);
void attemptAddHouse(int x, int y);

int main()
{
	FILE* fp = fopen("input.txt", "r");
	char bufChar = 0;
	char eofreached = fscanf(fp, "%c", &bufChar);
	houseListHead = initHouse(0,0);
	int x = 0; // x and y are at the bottom left by mathematical convention
	int y = 0;
	while(eofreached != EOF)
	{
		switch(bufChar)
		{
		case 'v':
			y--;
			break;
		case '^':
			y++;
			break;
		case '>':
			x++;
			break;
		case '<':
			x--;
			break;
		}	
		attemptAddHouse(x,y);
		eofreached = fscanf(fp, "%c", &bufChar);
	}
	house_l* ptr = houseListHead;
	int count = 0;
	while(ptr != NULL)
	{
		count++;
		ptr = ptr->next;
	}
	printf("total: %d\n", count);
}

house_l* initHouse(int x, int y)
{
	house_l* ptr = malloc(sizeof(house_l));
	if(ptr == NULL)
	{
		printf("failed malloc");
		return NULL;
	}
	ptr->x = x;
	ptr->y = y;
	ptr->next = NULL;
	return ptr;
}

void attemptAddHouse(int x, int y)
{
	house_l* ptr = houseListHead;
	while(ptr != NULL)
	{
		if(ptr->x == x && ptr->y == y)
		{ // we are delivering back to the same house
			return;
		}
		if(ptr->next == NULL)
			break;
		ptr = ptr->next;
	}
	// we are pointing at the end of the linked list
	ptr->next = initHouse(x,y);
}
