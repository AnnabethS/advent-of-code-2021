#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define WORDSBEFORE 10
#define WORDSAFTER 4
#define MAXCHARS 7

#ifdef DEBUG
#define FILENAME "test.txt"
#define LINES 10
#else
#define FILENAME "input.txt"
#define LINES 200
#endif

typedef struct line
{
	char inputSignals[WORDSBEFORE][MAXCHARS+1];
	char outputSegments[WORDSAFTER][MAXCHARS+1];
} line;

int doLine(line* l);

void printLine(line* l);

void printAllLines(line lines[LINES]);

void printSegments(int seg[7]);

int getValueOfSignalString(char* signalString, int segment[7]);

void printInputWords(char* words[WORDSBEFORE]);

// string must be null terminated or bad things will happen
char isCharInString(char* string, char c);

int main()
{
	FILE* fp = fopen(FILENAME, "r");
	char bufStr[MAXCHARS+1]; //+1 for null terminator
	char delimPassed = 0;

	line lines[LINES];


	for(int i=0; i < LINES; i++)
	{
		delimPassed = 0;
		for(int j=0; j < WORDSBEFORE+WORDSAFTER+1; j++)
		{
			fscanf(fp, "%s", bufStr);
			if(bufStr[0]=='|')
				delimPassed = 1;
			else if (delimPassed)
			{ //output words
				strcpy(lines[i].outputSegments[j-(WORDSBEFORE+1)], bufStr);
			}
			else
			{ //input words
				strcpy(lines[i].inputSignals[j], bufStr);
			}
		}
	}

	/* for(int i=0; i < LINES; i++) */
	/* { */
	/* 	printf("INPUT: "); */
	/* 	for(int j=0; j < WORDSBEFORE; j++) */
	/* 	{ */
	/* 		printf("%s ", lines[i].inputSignals[j]); */
	/* 	} */
	/* 	printf("\n"); */
	/* 	printf("OUTPUT: "); */
	/* 	for(int j=0; j < WORDSAFTER; j++) */
	/* 	{ */
	/* 		printf("%s ", lines[i].outputSegments[j]); */
	/* 	} */
	/* 	printf("\n\n"); */
	/* } */

	/* printLine(&lines[2]); */
	/* printf("%d\n", doLine(&lines[2])); */

	int total=0;
	for(int i=0; i < LINES; i++)
	{
		total += doLine(&lines[i]);
	}

	printf("total %d", total);

	return 0;
}

int doLine(line* l)
{
	// the signal that is needed to light up the segment
	int segment[7];
	for(int i=0; i < 7; i++)
		segment[i] = -1;

	// points to the first char of input word for the digit which is the index
	char* inputWords[10];
	for(int i=0; i < 10; i++)
		inputWords[i] = NULL;

	// define the input words for 1,4,7,8
	for(int i=0; i < WORDSBEFORE; i++)
	{
		switch(strlen(l->inputSignals[i]))
		{
		case(2):
			inputWords[1] = &l->inputSignals[i][0];
			break;
		case(3):
			inputWords[7] = &l->inputSignals[i][0];
			break;
		case(4):
			inputWords[4] = &l->inputSignals[i][0];
			break;
		case(7):
			inputWords[8] = &l->inputSignals[i][0];
			break;
		}
	}

	// iterate through all 3 chars in the input word for 7
	char* currChar = inputWords[7];
	for(int i=0; i < 3; i++)	
	{
		if(!isCharInString(inputWords[1], *currChar))
			break;
		currChar++;
	}
	segment[0] = *currChar;

	
	// get the possible values for 2,5 and 1,3
	
	char possible25[2] = {inputWords[1][0], inputWords[1][1]};
	char possible13[2];
	char x=0;
	for(int i=0; i < 4; i++)
	{
		if(possible25[0]!=inputWords[4][i] & possible25[1]!=inputWords[4][i])
		{
			possible13[x] = inputWords[4][i];
			x++;
		}
	}



	// find the 5-len input word with 1 value from 2,5 and both from 1,3
	

	for(char i=0; i < WORDSBEFORE; i++)
	{
		if(strlen(l->inputSignals[i]) != 5)
			continue;
		if(
				(isCharInString(l->inputSignals[i], possible25[0]) ^ isCharInString(l->inputSignals[i], possible25[1])) &&
				(isCharInString(l->inputSignals[i], possible13[0]) ^ isCharInString(l->inputSignals[i], possible13[1])))
		{
			inputWords[2] = l->inputSignals[i];
		}
	}



	// find the signals for segments 2 and 3 by eliminating from the word, since
	// we know the value for 2 or 5 and we know the value for 1 or 3
	if(isCharInString(inputWords[2], possible25[0]))
		segment[2] = possible25[0];
	else
		segment[2] = possible25[1];

	if(isCharInString(inputWords[2], possible13[0]))
		segment[3] = possible13[0];
	else
		segment[3] = possible13[1];


	// find 5 from knowing the values for 2 and 5 but not which way round
	// and now we know the value of 2
	if(inputWords[1][0]==segment[2])
		segment[5] = inputWords[1][1];
	else if (inputWords[1][1]==segment[2])
		segment[5] = inputWords[1][0];
	else
		printf("unreachable (hopefully)");


	// find the input word for displaying 4, eliminate the signals for 
	// 2,3,5 to leave only the signal for segment 1
	for(int i=0; i < 4; i++)
	{
		if(inputWords[4][i] != segment[2] && inputWords[4][i] != segment[3] &&
			inputWords[4][i] != segment[5])
		{
			segment[1] = inputWords[4][i];
			break;
		}
	}


	// find the input word for 3 by finding the only 2 unknown 5 length input
	// words, and then pick the one that has the signal for segment 2 in it
	for(int i=0; i < WORDSBEFORE; i++)
	{
		if(strlen(l->inputSignals[i]) == 5 && l->inputSignals[i] != inputWords[2])
		{
			if(isCharInString(l->inputSignals[i], segment[2]))
			{
				inputWords[3] = l->inputSignals[i];
			}
		}
	}


	// we know all signals in the input word for 3, except for the signal for 6
	for(int i=0; i < 5; i++)
	{
		if(inputWords[3][i] != segment[0] && inputWords[3][i] != segment[2] &&
			inputWords[3][i] != segment[3] && inputWords[3][i] != segment[5])
		{
			segment[6] = inputWords[3][i];
			break;
		}
	}


	// the signal for segment 4 is the only one left.
	
	char allChars[8] = "abcdefg\0";
	char found = 0;

	for(int i=0; i < 7; i++)
	{
		found = 0;
		for (int j=0; j < 7; j++)
		{
			if(allChars[i] == segment[j])
			{
				found = 1;
			}
		}
		if(!found)
		{
			segment[4] = allChars[i];
		}
	}


	// we now have all segments defined

	int total = 0;

	for(int i=0; i < WORDSAFTER; i++)
	{
		total += pow(10, WORDSAFTER-1-i) * getValueOfSignalString(l->outputSegments[i], segment);
	}


	return total;
}

void printLine(line* l)
{
	printf("INPUT: ");
	for(int j=0; j < WORDSBEFORE; j++)
	{
		printf("%s ", l->inputSignals[j]);
	}
	printf("\n");
	printf("OUTPUT: ");
	for(int j=0; j < WORDSAFTER; j++)
	{
		printf("%s ", l->outputSegments[j]);
	}
	printf("\n");
}

void printAllLines(line lines[LINES])
{
	for(int i=0; i < LINES; i++)
		printLine(&lines[i]);
	printf("\n");
}

char isCharInString(char* string, char c)
{
	char* currChar = string;

	while(*currChar != '\0')
	{
		if(*currChar == c)
			return 1;
		currChar++;
	}
	return 0;
}

void printSegments(int seg[7])
{
	for(int i=0; i < 7; i++)
	{
		if(seg[i]==-1)
			printf("? ");
		else
			printf("%c ", seg[i]);
	}
	printf("\n");
}

int getValueOfSignalString(char* signalString, int segment[7])
{
	// get the easy length-only stuff out of the way
	if(strlen(signalString) == 2)
		return 1;
	else if(strlen(signalString) == 3)
		return 7;
	else if(strlen(signalString) == 4)
		return 4;
	else if(strlen(signalString) == 7)
		return 8;
	else if(strlen(signalString) == 6)
	{ // its either 0 6 or 9. 6 has a 3, whereas 0 does not
		if(!isCharInString(signalString, segment[3]))
			return 0;
		else if (isCharInString(signalString, segment[4]))
			return 6;
		else
			return 9;
	}
	else
	{ // here we deal with 5-length strings
		if(isCharInString(signalString, segment[4]))
			// 2 is the only option if 4 is in the string
			return 2;
		else if(isCharInString(signalString, segment[2]))
			return 3;
		else
			return 5;
	}
}

void printInputWords(char* words[WORDSBEFORE])
{
	for(int i=0; i < WORDSBEFORE; i++)
	{
		if(words[i]==NULL)
			printf("NULL ");
		else
			printf("%s ", words[i]);
	}
	printf("\n");
}
