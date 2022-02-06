#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FILENAME "input.txt"
#define BUFLEN 9

int main()
{
	FILE* fp = fopen(FILENAME, "r");
	char bufStr[BUFLEN] = {0};
	char eofcheck = 0;
	fscanf(fp, "%s", bufStr);
	int total = 0;
	while(eofcheck != EOF)
	{
		int l = strtol(strtok(bufStr, "x"), NULL, 10);
		int w = strtol(strtok(NULL, "x"), NULL, 10);
		int h = strtol(strtok(NULL, "x"), NULL, 10);
		/* int l = 2; */
		/* int w = 3; */
		/* int h = 4; */
		int p1 = 2*l + 2*w;
		int p2 = 2*l + 2*h;
		int p3 = 2*w + 2*h;
		int smallP = p1;
		if(smallP > p2)
			smallP = p2;
		if(smallP > p3)
			smallP = p3;
		total += (smallP) + (l * w * h);
		eofcheck = fscanf(fp, "%s", bufStr);
	}
	printf("total: %d\n", total);
}
