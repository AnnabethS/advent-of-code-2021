#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFLEN 30000

char* input;
char* excluded;

int main()
{
	input = calloc(BUFLEN, sizeof(char));
	excluded = calloc(BUFLEN, sizeof(char));
	FILE* fp = fopen("input.txt", "r");
	fscanf(fp, "%s", input);
	fclose(fp);
	char* next_red = strstr(input, ":\"red\"");
	while(next_red != NULL)
	{
		next_red = strstr(next_red+1, ":\"red\"");
	}
}

char is_in_object(char* ptr)
{
	while(*ptr != '{' && *ptr != '[')
	{
		ptr--;
	}
	return *ptr=='{';
}

void mark_object_excluded(char* ptr)
{
	if (*ptr != '{')
	{
		printf("bad data passed to object excluded, expected {, but got %c\n", *ptr);
		return;
	}

	int bracket_amount = 1;
	char* orig_ptr = ptr;
	ptr++;
	while(bracket_amount > 0)
	{
		if(*ptr == '{')
			bracket_amount++;
		else if(*ptr=='}')
			bracket_amount--;
		ptr++;
	}
	ptr--;

}
