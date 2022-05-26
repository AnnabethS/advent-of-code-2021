#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef DEBUG
#define BUFLEN 30000
#else
#define BUFLEN 50
#endif

char* input;
char* excluded;

char is_in_object(char* ptr);
void mark_object_excluded(char* ptr);

int main()
{
	input = calloc(BUFLEN, sizeof(char));
	excluded = calloc(BUFLEN, sizeof(char));
    #ifdef DEBUG
    strcpy(input, "{\"a\":{\"b\":[], \"c\":\"red\"}}");
    #else
	FILE* fp = fopen("input.txt", "r");
	fscanf(fp, "%s", input);
	fclose(fp);
    #endif
	char* next_red = strstr(input, ":\"red\"");
	while(next_red != NULL)
	{
		if(is_in_object(next_red))
			mark_object_excluded(next_red);
		next_red = strstr(next_red+1, ":\"red\"");
	}
    char* ptr = input;
    /* while(*ptr != 0) */
    /* { */
    /*     if(!*(excluded + (ptr-input))) */
    /*         printf("%c", *(input + (ptr-input))); */
    /*     ptr++; */
    /* } */
    printf("\n");

    // count numbers
	char lastCharWasNum = 0;
	char numBuffer[10] = {0};
	int total = 0;
	for(int i=0; i < BUFLEN && input[i]; i++)
	{
        if(!excluded[i])
        {
            if((input[i] == '-' || (input[i] >= '0' && input[i] <= '9')))
            {
                strncat(numBuffer, &input[i], 1);
                lastCharWasNum = 1;
            }
            else if(lastCharWasNum)
            {
                int x = strtol(numBuffer, NULL, 10);
                total += x;
                lastCharWasNum = 0;
                memset(numBuffer, 0, sizeof(char)*10);
            }
        }
	}
	printf("total: %d\n", total);
}

char is_in_object(char* ptr)
{
    int objBracketAmount = 0;
    int arrBracketAmount = 0;
	while(objBracketAmount >= 0 && arrBracketAmount >= 0)
	{
        if(*ptr == '}')
            objBracketAmount++;
        else if (*ptr == '{')
            objBracketAmount--;
        else if (*ptr == ']')
            arrBracketAmount++;
        else if (*ptr== '[')
            arrBracketAmount--;
		ptr--;
	}
	return objBracketAmount < 0;
}

void mark_object_excluded(char* ptr)
{
	int bracket_amount = 0;
	while(bracket_amount >= 0)
	{
		if(*ptr == '{')
			bracket_amount--;
		else if(*ptr=='}')
			bracket_amount++;
		ptr--;
	}
	/* printf("%c\n", *ptr); */

	bracket_amount = 0;
	ptr++;
	ptr++;
	printf("%c\n", *ptr);
	char* orig_ptr = ptr;
	while(bracket_amount >= 0)
	{
		/* printf("%c", *ptr); */
        *(excluded + (ptr-input)) = 1;
		if(*ptr == '{')
			bracket_amount++;
		else if(*ptr=='}')
			bracket_amount--;
		ptr++;
	}
	/* printf("\n"); */
	ptr--;
    *(excluded + (ptr-input)) = 0;
}
