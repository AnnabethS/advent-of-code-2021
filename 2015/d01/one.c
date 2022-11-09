#include <stdio.h>

#define FILENAME "input.txt"
#define BUFSTRSIZE 7001

int main()
{
	FILE* fp = fopen(FILENAME, "r");
	char x = 'a';
	int floor = 0;
	fscanf(fp, "%c", &x);
	char eofreached = 0;
	while(eofreached != EOF)
	{
		printf("%c\n", x);
		if(x == ')')
			floor--;
		else if(x == '(')
			floor++;
		eofreached = fscanf(fp, "%c", &x);
	}
	printf("%d\n", floor);
}
