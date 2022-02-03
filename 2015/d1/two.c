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
	int i=1;
	while(eofreached != EOF)
	{
		if(x == ')')
			floor--;
		else if(x == '(')
			floor++;
		if(floor < 0)
			break;
		eofreached = fscanf(fp, "%c", &x);
		i++;
	}
	printf("%d\n", i);
}
