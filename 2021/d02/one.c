#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
	// oops i forgot to make a different file for part 2,
	// my part 1 solution was basically the same anyway, but more boring
	FILE *fp;
	fp = fopen("input.txt", "r");

	char eofreached;
	char bufStr[10];
	int bufInt;
	int hPos = 0;
	int vPos = 0;
	int aim = 0;
	int count = 0;

	eofreached = fscanf(fp, "%s %d", bufStr, &bufInt);

	while (eofreached != EOF)
	{
		if(bufStr[0] == 'f')
		{
			hPos += bufInt;
			vPos += aim*bufInt;
		}
		else if (bufStr[0] == 'd')
			aim += bufInt;
		else if (bufStr[0] == 'u')
			aim -= bufInt;
		else
			printf("unknown str...\n");
		if (count <= 20)
			printf("hPos: %d, vPos: %d, aim: %d\n", hPos, vPos, aim);
		count++;
		eofreached = fscanf(fp, "%s %d", bufStr, &bufInt);
	}
	fclose(fp);
	long multPos;
	multPos = hPos*vPos;
	printf("vPos: %d, hPos: %d, multPos: %ld\n", vPos, hPos, multPos);
}
