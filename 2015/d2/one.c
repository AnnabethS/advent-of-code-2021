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
		printf("%d %d %d\n", l, w, h);
		int a1 = l*w;
		int a2 = l*h;
		int a3 = w*h;
		int a4;
		if(a1 < a2)
			a4 = a1;
		else
			a4 = a2;
		if(a3 < a4)
			a4 = a3;
		total += a1*2 + a2*2 + a3*2 + a4;
		eofcheck = fscanf(fp, "%s", bufStr);
	}
	printf("total: %d\n", total);
}
