#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define WORDSBEFORE 10
#define WORDSAFTER 4
#define MAXCHARS 7

#ifdef DEBUG
#define FILENAME "test.txt"
#define LINES 10
#else
#define FILENAME "input.txt"
#define LINES 200
#endif

int main()
{
	FILE* fp = fopen(FILENAME, "r");
	char bufStr[MAXCHARS+1]; //+1 for null terminator
	char delimPassed = 0;

	int timesAppeared[10];
	for(int i=0; i<10; i++)
		timesAppeared[i]=0;

	for(int line=0; line < LINES; line++)
	{
		delimPassed = 0;
		for(int i=0; i < WORDSBEFORE+WORDSAFTER+1; i++)
		{
			fscanf(fp, "%s", bufStr);
			if(bufStr[0]=='|')
				delimPassed = 1;
			else if (delimPassed)
			{
				for(int j=0; j < MAXCHARS+1; j++)
				{
					if(bufStr[j]=='\0')
					{
						// j is the position of the null terminator, not
						// the last real char of the string
						switch(j)
						{
						case(2):
							timesAppeared[1]++;
							break;
						case(4):
							timesAppeared[4]++;
							break;
						case(3):
							timesAppeared[7]++;
							break;
						case(7):
							timesAppeared[8]++;
							break;
						}
						break;
					}
				}
			}
		}
	}

	int total=0;
	for(int i=0; i < 10; i++)
	{
		printf("%d appeared %d times\n", i, timesAppeared[i]);
		total += timesAppeared[i];
	}

	printf("tracked appearances in total: %d\n", total);

	return 0;
}
