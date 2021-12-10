#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#ifdef TEST
#define FILENAME "test.txt"
#define MAXLINELEN 24
#define LINES 10
#else
#define FILENAME "input.txt"
#define MAXLINELEN 200
#define LINES 90
#endif

long long checkLine(char* line);

void printStack(char* stackStart);

int mysort(const void *a, const void *b)
{
	if(*(long long*)a == -1 && *(long long*)b == -1)
	{
		return 0;
	}
	else if(*(long long*)a == -1)
	{
		return 1;
	}
	else if(*(long long*)b == -1)
	{
		return -1;
	}
	else if(*(long long*)a == *(long long*)b)
	{
		return 0;
	}
	else if(*(long long*)a > *(long long*)b)
		return 1;
	else if(*(long long*)a < *(long long*)b)
		return -1;
	printf("error in cmpfunc, a: %lld b: %lld\n", *(long long*)a, *(long long*)b);
	return 0;
}

int main()
{
	FILE* fp = fopen(FILENAME, "r");
	char bufStr[MAXLINELEN+1];

	fscanf(fp, "%s", bufStr);

	printf("%s\n", bufStr);

	char eofreached = 0;
	long long totals[LINES] = {-1};

	/* total = checkLine(bufStr); */
	/* printf("total %d\n", total); */
	/* fscanf(fp, "%s", bufStr); */
	/* total = checkLine(bufStr); */

	int count = 0;
	while(eofreached != EOF)
	{
		long long lineval = checkLine(bufStr);
		printf("%lld\n", lineval);
		if(lineval != -1)
		{
			totals[count] = lineval;
			count++;
		}
		eofreached = fscanf(fp, "%s", bufStr);
	}

	qsort(totals, count, sizeof(long long), mysort);

	for(int i=0; i < count; i++)
	{
		printf("%d: %lld\n", i, totals[i]);
	}

	printf("middle: %lld\n", totals[(count)/2]);

}

long long checkLine(char* line)
{
	printf("\n\n%s\n", line);
// points to position 0 of the stack, back past this is undefined
	char* stackStart;

	// points to the top element of the stack, or position 0, if empty
	char* stackHead;

	stackStart = (char*) calloc(sizeof(char), (MAXLINELEN/2)+1);
	stackHead = stackStart;

	char next = 0;
	char corrupt = 0;
	long long total = 0;

	for(int j=0; j < MAXLINELEN; j++)
	{
		#ifdef DEBUG
		printStack(stackStart);
		printf(" | pointpos %-2ld, topChar: %c bufChar: %c\n", stackHead-stackStart, *stackHead, line[j]);
		#endif

		switch (line[j])
		{
			case(0):
				next=1;
				break;
			case('{'):
			case('['):
			case('<'):
			case('('):
				if(stackHead != stackStart)
					stackHead++;
				else if(*stackHead != 0)
					stackHead++;
				*stackHead = line[j];
				break;
			case('}'):
				if(*stackHead == '{')
				{
					*stackHead = 0;
					stackHead--;
					if(stackHead<stackStart)
						stackHead = stackStart;
				}
				else
				{
					next = 1;
					corrupt = 1;
				}
				break;
			case(']'):
				if(*stackHead == '[')
				{
					*stackHead = 0;
					stackHead--;
					if(stackHead<stackStart)
						stackHead = stackStart;
				}
				else
				{
					next = 1;
					corrupt =1;
				}
				break;
			case('>'):
				if(*stackHead == '<')
				{
					*stackHead = 0;
					stackHead--;
					if(stackHead<stackStart)
						stackHead = stackStart;
				}
				else
				{
					next = 1;
					corrupt = 1;
				}
				break;
			case(')'):
				if(*stackHead == '(')
				{
					*stackHead = 0;
					stackHead--;
					if(stackHead<stackStart)
						stackHead = stackStart;
				}
				else
				{
					next = 1;
					corrupt = 1;
				}
				break;
		}
		if(next)
		{
			/* for(int k=0; k < (MAXLINELEN/2); k++) */
			/* 	*(stackStart + k) = 0; */
			break;
		}
	}
	if(corrupt)
		return -1;
	
	while(*stackHead != 0)
	{
		total *= 5;
		switch(*stackHead)
		{
			case('('):
				total += 1;
				break;
			case('['):
				total += 2;
				break;
			case('{'):
				total += 3;
				break;
			case('<'):
				total += 4;
				break;
		}
		*stackHead = 0;
		stackHead--;
		if(stackHead<stackStart)
			stackHead = stackStart;
	}

	free(stackStart);
	return total;
}

void printStack(char* stackStart)
{
	for(int i=0; i < (MAXLINELEN/2)+1; i++)
	{
		if(*(stackStart+i) != 0)
			printf("%c", *(stackStart+i));
		else
			printf(" ");
	}
}
