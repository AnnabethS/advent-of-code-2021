#include <stdio.h>
#include <string.h>

#define BUFLEN 16

char isNice(char* str);

int main()
{
	FILE* fp = fopen("input.txt", "r");
	char buf[BUFLEN] = {0};
	char eofreached = fscanf(fp, "%s\n", &buf[0]);
	int niceCount = 0;
	while(eofreached != EOF)
	{
		if(isNice(&buf[0]))
		{
			niceCount++;
		}
		eofreached = fscanf(fp, "%s\n", &buf[0]);
	}
	printf("nice strings: %d\n", niceCount);
}

char isNice(char* str)
{
	int vowelAmount = 0;

	char containsDouble = 0;
	
	int len = strlen(str);

	for(int i=0; i < len; i++)
	{
		vowelAmount += *(str + i) == 'a' ||
		   *(str + i) == 'e' ||
		   *(str + i) == 'i' ||
		   *(str + i) == 'o' ||
			*(str + i) == 'u';

		if(i < (len-1))
		{
			char fst = *(str+i);
			char snd = *(str+i+1);
			if(fst == snd)
				containsDouble = 1;
			if((fst == 'a' && snd == 'b') ||
			   (fst == 'c' && snd == 'd') ||
			   (fst == 'p' && snd == 'q') ||
			   (fst == 'x' && snd == 'y'))
			{
				return 0;
			}
		}
	}

	return vowelAmount >= 3 && containsDouble;
}
