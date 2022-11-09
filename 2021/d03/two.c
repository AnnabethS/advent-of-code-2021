#include <stdio.h>
#include <string.h>
#include <math.h>

#define BITLENGTH 12
#define ARRAYLENGTH	1000

int base2toBase10(char binaryInput[BITLENGTH]);
char getMostCommonBit(char arr[ARRAYLENGTH][BITLENGTH+1], int bit);
int getAmountRemainingStrings(char arr[ARRAYLENGTH][BITLENGTH+1]);
void eliminateStrings(char arr[ARRAYLENGTH][BITLENGTH+1], int bit, char remove);

int main()
{
	FILE *fp;
	fp = fopen("input.txt", "r");

	char eofreached;
	char bufStr[BITLENGTH+1];
	char oxArray[ARRAYLENGTH][BITLENGTH+1];
	char coArray[ARRAYLENGTH][BITLENGTH+1];
	int ones = 0;
	int count = 0;

	eofreached = fscanf(fp, "%s", bufStr);

	while (eofreached != EOF)
	{
		strcpy(oxArray[count], bufStr);
		strcpy(coArray[count], bufStr);
		oxArray[count][BITLENGTH] = '\0';
		count++;
		eofreached = fscanf(fp, "%s", bufStr);
	}

	fclose(fp);

	int currBit = 0;
	while(getAmountRemainingStrings(oxArray) > 1)
	{
		char bit = getMostCommonBit(oxArray, currBit);
		if(bit=='0')
		{
			eliminateStrings(oxArray, currBit, '1');
		}
		else if (bit == '1')
		{
			eliminateStrings(oxArray, currBit, '0');
		}
		else
		{
			eliminateStrings(oxArray, currBit, '0');
		}
		currBit++;
	}
	char oxString[BITLENGTH+1];
	for(int i=0; i < ARRAYLENGTH; i++)
	{
		if(oxArray[i][0] != 'n')
		{
			strcpy(oxString, oxArray[i]);
			break;
		}
	}

	int oxNum = base2toBase10(oxString);

	currBit = 0;
	while(getAmountRemainingStrings(coArray) > 1)
	{
		char bit = getMostCommonBit(coArray, currBit);
		if(bit=='0' || bit=='1')
			eliminateStrings(coArray, currBit, bit);
		else
			eliminateStrings(coArray, currBit, '1');
		currBit++;
	}
	char coString[BITLENGTH+1];
	for (int i=0; i < ARRAYLENGTH; i++)
	{
		if (coArray[i][0] != 'n')
		{
			strcpy(coString, coArray[i]);
			break;
		}
	}


	int coNum = base2toBase10(coString);

	printf("%s:%d | %s:%d\n", oxString, oxNum, coString, coNum);

	int lifeSupportNum = coNum * oxNum;
	printf("Life Support Num: %d\n", lifeSupportNum);

	/* printf("%d\n", getAmountRemainingStrings(oxArray)); */
	/* printf("%c\n", getMostCommonBit(oxArray, 0)); */
	/* eliminateStrings(oxArray, 0, '1'); */
	/* printf("%d\n", getAmountRemainingStrings(oxArray)); */


	return 0;
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

char getMostCommonBit(char arr[ARRAYLENGTH][BITLENGTH+1], int bit)
{
	int ones = 0;
	int zeros = 0;
	for (int i=0; i < ARRAYLENGTH; i++)
	{
		if (arr[i][0]=='n')
			continue;
		else if(arr[i][bit]=='0')
			zeros++;
		else
			ones++;
	}
	if (ones > zeros)
		return '1';
	else if (ones < zeros)
		return '0';
	else
		return '2';
}

int getAmountRemainingStrings(char arr[ARRAYLENGTH][BITLENGTH+1])
{
	int count = 0;
	for (int i=0; i < ARRAYLENGTH; i++)
	{
		if(arr[i][0] != 'n')
			count++;
	}
	return count;
}

void eliminateStrings(char arr[ARRAYLENGTH][BITLENGTH+1], int bit, char remove)
{
	for (int i=0; i < ARRAYLENGTH; i++)
	{
		if(arr[i][bit] == remove)
			arr[i][0] = 'n';
	}
}
