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
		eofcheck = fscanf(fp, "%s", bufStr);
	}
	printf("total: %d\n", total);
}
