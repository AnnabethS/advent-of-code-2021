#include <stdio.h>
#include <stdlib.h>

#ifdef TEST
#define FILENAME "test.txt"
#define MAXLINELEN 24
#else
#define FILENAME "input.txt"
#define MAXLINELEN 200
#endif

int checkLine(char* line);

void printStack(char* stackStart);

int main()
{
	FILE* fp = fopen(FILENAME, "r");
	char bufStr[MAXLINELEN+1];

	fscanf(fp, "%s", bufStr);

	printf("%s\n", bufStr);

	char eofreached = 0;
	int total = 0;

	/* total = checkLine(bufStr); */
	/* printf("total %d\n", total); */
	/* fscanf(fp, "%s", bufStr); */
	/* total = checkLine(bufStr); */

	while(eofreached != EOF)
	{
		total += checkLine(bufStr);
		eofreached = fscanf(fp, "%s", bufStr);
	}

	printf("total: %d\n", total);
}

int checkLine(char* line)
{
	printf("\n\n%s\n", line);
// points to position 0 of the stack, back past this is undefined
	char* stackStart;

	// points to the top element of the stack, or position 0, if empty
	char* stackHead;

	stackStart = (char*) calloc(sizeof(char), (MAXLINELEN/2)+1);
	stackHead = stackStart;

	char next = 0;
	int total = 0;

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
					total += 1197;
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
					total += 57;
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
					total += 25137;
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
					total += 3;
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
