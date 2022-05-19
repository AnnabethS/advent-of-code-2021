#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
	int children;
	int cats;
	int sDogs;
	int pDogs;
	int aDogs;
	int vDogs;
	int goldfish;
	int trees;
	int cars;
	int perfumes;
	char valid;
}aunt;

// very important, the input is 1-indexed
aunt aunts[500] = {-1};
aunt goalAunt = {3, 7, 2, 3, 0, 0, 5, 3, 2, 1};
FILE* fp;

void parseAunt(int num);
void setAuntValue(aunt* a, char* str, int x);
void printAunt(aunt* a);

int main()
{
	memset(aunts, (-1), sizeof(aunt)*500);
	fp = fopen("input.txt", "r");
	for(int i=0; i < 500; i++)
	{
		parseAunt(i);
	}

	for(int i=0; i < 500; i++)
	{
		printAunt(&aunts[i]);
		if((aunts[i].children != goalAunt.children) && (aunts[i].children != -1))
		{
			aunts[i].valid = 0;
			continue;
		}
		if(!(aunts[i].cats > goalAunt.cats) && !(aunts[i].cats == -1))
		{
			aunts[i].valid = 0;
			continue;
		}
		if(!(aunts[i].sDogs == goalAunt.sDogs) && !(aunts[i].sDogs == -1))
		{
			aunts[i].valid = 0;
			continue;
		}
		if(!(aunts[i].pDogs < goalAunt.pDogs) && !(aunts[i].pDogs == -1))
		{
			aunts[i].valid = 0;
			continue;
		}
		if(!(aunts[i].aDogs == goalAunt.aDogs) && !(aunts[i].aDogs == -1))
		{
			aunts[i].valid = 0;
			continue;
		}
		if(!(aunts[i].vDogs == goalAunt.vDogs) && !(aunts[i].vDogs == -1))
		{
			aunts[i].valid = 0;
			continue;
		}
		if(!(aunts[i].goldfish < goalAunt.goldfish) && !(aunts[i].goldfish == -1))
		{
			aunts[i].valid = 0;
			continue;
		}
		if(!(aunts[i].trees > goalAunt.trees) && !(aunts[i].trees == -1))
		{
			aunts[i].valid = 0;
			continue;
		}
		if(!(aunts[i].cars == goalAunt.cars) && !(aunts[i].cars == -1))
		{
			aunts[i].valid = 0;
			continue;
		}
		if(!(aunts[i].perfumes == goalAunt.perfumes) && !(aunts[i].perfumes == -1))
		{
			aunts[i].valid = 0;
			continue;
		}
	}

	for(int i=0; i < 500; i++)
	{
		if(aunts[i].valid)
		{
			printf("valid: %d\n", i+1);
			break;
		}
	}
}

void parseAunt(int num)
{
	aunts[num].valid = 1;
	char waste[20] = {0};

	char item1[20] = {0};
	char val1[5] = {0};

	char item2[20] = {0};
	char val2[5] = {0};

	char item3[20] = {0};
	char val3[5] = {0};

	fscanf(fp, "%s %s %s %s %s %s %s %s", waste, waste, item1, val1, item2, val2, item3, val3);

	int v1 = strtol(val1, NULL, 10);
	int v2 = strtol(val2, NULL, 10);
	int v3 = strtol(val3, NULL, 10);

	char* y;
	y = strtok(item1, ":");
	setAuntValue(&aunts[num], y, v1);
	y = strtok(item2, ":");
	setAuntValue(&aunts[num], y, v2);
	y = strtok(item3, ":");
	setAuntValue(&aunts[num], y, v3);
}


void setAuntValue(aunt* a, char* str, int x)
{
	if(strcmp(str, "children") == 0)
	{
		a->children = x;
	}
	else if(strcmp(str, "cats") == 0)
	{
		a->cats = x;
	}
	else if(strcmp(str, "samoyeds") == 0)
	{
		a->sDogs = x;
	}
	else if(strcmp(str, "pomeranians") == 0)
	{
		a->pDogs = x;
	}
	else if(strcmp(str, "akitas") == 0)
	{
		a->aDogs = x;
	}
	else if(strcmp(str, "vizslas") == 0)
	{
		a->vDogs = x;
	}
	else if(strcmp(str, "goldfish") == 0)
	{
		a->goldfish = x;
	}
	else if(strcmp(str, "trees") == 0)
	{
		a->trees = x;
	}
	else if(strcmp(str, "cars") == 0)
	{
		a->cars = x;
	}
	else if(strcmp(str, "perfumes") == 0)
	{
		a->perfumes = x;
	}
	else
	{
		printf("unreachable\n");
	}
}

void printAunt(aunt *a)
{
	printf("%2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d\n", a->children, a->cats, a->sDogs, a->pDogs,
		   a->aDogs, a->vDogs, a->goldfish, a->trees, a->cars, a->perfumes, a->valid);
}

