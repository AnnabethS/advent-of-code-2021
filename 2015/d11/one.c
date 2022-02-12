#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRLEN 8

void increment(char *pass, int pos);
char isValid(char* pass);

int main()
{
	char pass[STRLEN+1] = "hepxcrrq";
	printf("%s\n", pass);
	while(!isValid(pass))
		increment(pass, 7);
	printf("%s\n", pass);
}

void increment(char* pass, int pos)
{
	if(pos < 0)
		return;
	pass[pos]++;
	if(pass[pos] > 'z')
	{
		pass[pos] = 'a';
		increment(pass, pos-1);
	}
}

char isValid(char* pass)
{
	//rule 1 - password must contain straight of 3
	char r1 = 0;
	for(int i=0; i < STRLEN-2; i++)
	{
		if(pass[i]+1 == pass[i+1] && pass[i+1]+1 == pass[i+2])
		{
			r1 = 1;
			break;
		}
	}
	if(!r1)
		return 0;

	//rule 2 - password cannot contain i o l

	for(int i=0; i < STRLEN; i++)
	{
		if(pass[i] == 'i' || pass[i] == 'o' || pass[i] == 'l')
			return 0;
	}

	//rule 3 - 2 distinct overlapping pairs

	char prevPair = 0;
	char pairs = 0;
	for(int i=0; i < STRLEN-1; i++)
	{
		if(pass[i]==pass[i+1] && pass[i] != prevPair)
		{
			pairs++;
			prevPair = pass[i];
			if(pairs==2)
				break;
		}
	}

	return pairs == 2;
}
