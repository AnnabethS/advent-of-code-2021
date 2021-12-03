#include <stdio.h>
#include <string.h>
#include <math.h>

#define BITLENGTH 12

int base2toBase10(char binaryInput[BITLENGTH]);

int main()
{
	FILE *fp;
	fp = fopen("input.txt", "r");

	char eofreached;
	char bufStr[BITLENGTH+1];
	int ones[BITLENGTH];
	int count = 0;

	for (int i=0; i<BITLENGTH; i++)
	{
		ones[i] = 0;
	}

	eofreached = fscanf(fp, "%s", bufStr);

	while (eofreached != EOF)
	{
		for(int i=0; i<BITLENGTH; i++)
		{
			if(bufStr[i]=='1')
				ones[i]++;
		}
		count++;
		eofreached = fscanf(fp, "%s", bufStr);
	}

	fclose(fp);

	char gammaRate[BITLENGTH+1];
	char epsilonRate[BITLENGTH+1];

	for (int i=0; i < BITLENGTH; i++)
	{
		printf("%d ", ones[i]);
	}
	printf("\n");

	for (int i=0; i < BITLENGTH; i++)
	{
		if(ones[i] < (count/2))
		{
			gammaRate[i] = '0';
			epsilonRate[i] = '1';
		}
		else
		{
			gammaRate[i] = '1';
			epsilonRate[i] = '0';
		}
		/* gammaRate[i] = (ones[i] < count/2); */
		/* epsilonRate[i] = (ones[i] > count/2); */
	}
	gammaRate[BITLENGTH] = '\0';
	epsilonRate[BITLENGTH] = '\0';

	printf("G: %s | E: %s\n", gammaRate, epsilonRate);
	int gammaNum = base2toBase10(gammaRate);
	int epsilonNum = base2toBase10(epsilonRate);

	int total = gammaNum * epsilonNum;

	printf("%d\n", total);
	return total;
}

int base2toBase10(char binaryInput[BITLENGTH])
{
	int total = 0;
	for (int i=0; i < BITLENGTH; i++)
	{
		if(binaryInput[(BITLENGTH-1)-i] == '1')
			total += pow(2, i);
	}
	return total;
}
