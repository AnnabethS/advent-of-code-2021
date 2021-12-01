#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	FILE *fp;
	fp = fopen("input.txt", "r");

	int prevNum;
	int currNum;
	char bufStr[4];
	int count = 0;
	int count2 = 0;
	char* ptr;
	char eofreached;


	eofreached = fscanf(fp, "%s\n", bufStr);
	prevNum = strtol(bufStr, NULL, 10);
	fscanf(fp, "%s\n", bufStr);
	currNum = strtol(bufStr, NULL, 10);

	while (eofreached != EOF)
	{
		count2++;
		if(count2<20)
			printf("prev: %d, curr: %d\n", prevNum, currNum);
		if(currNum >= prevNum)
			count++;
		prevNum = currNum;
		eofreached = fscanf(fp, "%s\n", bufStr);
		currNum = strtol(bufStr, NULL, 10);
	}
	printf("times increased: %d\ncomparisons made: %d\n", count, count2);

	return 0;
}
