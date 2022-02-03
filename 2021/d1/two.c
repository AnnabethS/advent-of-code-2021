#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int calculate3Total(int input[2000], int index);

int main()
{
	FILE *fp;
	fp = fopen("input.txt", "r");

	int input[2000];
	char bufStr[4];
	int count = 0;
	char eofreached;
	
	while (eofreached != EOF)
	{
		eofreached = fscanf(fp, "%s\n", bufStr);
		input[count] = strtol(bufStr, NULL, 10);
		count++;
	}

	fclose(fp);

	int prevNum = 0;
	int timesIncreased = 0;
	int currNum = 0;

	prevNum = calculate3Total(input, 2);

	for (int i=3; i<2000; i++)
	{
		currNum = calculate3Total(input, i);
		if (currNum > prevNum)
			timesIncreased++;
		prevNum = currNum;
	}

	printf("times increased: %d\n", timesIncreased);

	return 0;
}

int calculate3Total(int input[2000], int index)
{
	if(index < 2)
		return -1;
	
	// valid input
	return (input[index] + input[index-1] + input[index-2]);
}
