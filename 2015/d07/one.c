#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define u16 uint16_t

enum op{
	OR, AND, NOT, RSHIFT, LSHIFT, ASSIGN
};

typedef struct gate{
	int in1[2]; //location of input 1
	int in2[2]; //location of input 2
	u16 val1; //value of input 1
	u16 val2; //value of input 2
	char const1; //1 if input 1 should be got from the val1 var
	char const2; //1 if input 2 should be got from the val2 var
	enum op inst; //the operation this gate performs
	int out[2]; //the location the output should be put
	char eval; //1 if this gate HAS been evaluated, 0 otherwise
}gate;

/* the first index is the first letter of the signal name
the second is the second letter, unless its ' ' which is
stored at index 26 */
u16 signals[26][27] = {0};
char defined[26][27] = {0};
gate gates[339] = {0};
FILE* fp;

// forward function definitions

/*
  Parses a single symbol, either a signal like "wq" or a literal 
Returns 0 when symbol cannot be evaluated because its undefined
otherwise returns 1
 */
char evalSymbol(char* ptr, u16* result);
char evalGate(gate *g);

// reads in a string symbol, writes the correct values to the gate passed
void parseSymbol(gate *g, int num, char* str);

//parses a line of input, and adds the gate to the gates list
char parseLine(gate* g);

void printSymbol(gate *g, int num);
void printGate(gate *g);
	
int main()
{
	fp = fopen("input.txt", "r");
	char check = 1;
	int count = 0;
	while(check)
	{
		check = parseLine(&gates[count]);
		count++;
	}

	check = 1;
	while(check)
	{
		check = 0;
		for(int i=0; i < 339; i++)
		{
			if(!gates[i].eval)
			{
				check = 1;
				evalGate(&gates[i]);
			}
		}
	}
	printf("%u\n", signals[0][26]);
}

/*
  attempts to evaluate a gate, returns 0 if not evaulated,
  returns 1 if correctly evaluated
 */
char evalGate(gate* g)
{
	u16 val1;
	u16 val2;
	if(g->const1)
	{
		val1 = g->val1;
	}
	else
	{
		if(defined[g->in1[0]][g->in1[1]])
		{
			val1 = signals[g->in1[0]][g->in1[1]];
		}
		else
		{
			return 0;
		}
	}
	if(g->inst != ASSIGN && g->inst != NOT)
	{
		if(g->const2)
			val2 = g->val2;
		else
		{
			if(defined[g->in2[0]][g->in2[1]])
			{
				val2 = signals[g->in2[0]][g->in2[1]];
			}
			else
				return 0;
		}
	}
	switch(g->inst)
	{
	case(OR):
		signals[g->out[0]][g->out[1]] = val1 | val2;
		defined[g->out[0]][g->out[1]] = 1;
		g->eval = 1;
		return 1;
	case(AND):
		signals[g->out[0]][g->out[1]] = val1 & val2;
		defined[g->out[0]][g->out[1]] = 1;
		g->eval = 1;
		return 1;
	case(RSHIFT):
		signals[g->out[0]][g->out[1]] = val1 >> val2;
		defined[g->out[0]][g->out[1]] = 1;
		g->eval = 1;
		return 1;
	case(LSHIFT):
		signals[g->out[0]][g->out[1]] = val1 << val2;
		defined[g->out[0]][g->out[1]] = 1;
		g->eval = 1;
		return 1;
	case(NOT):
		signals[g->out[0]][g->out[1]] = ~val1;
		defined[g->out[0]][g->out[1]] = 1;
		g->eval = 1;
		return 1;
	case(ASSIGN):
		printf("%d %d\n", g->out[0], g->out[1]);
		signals[g->out[0]][g->out[1]] = val1;
		defined[g->out[0]][g->out[1]] = 1;
		g->eval = 1;
		return 1;
	}
}

char evalSymbol(char* ptr, u16* result)
{
	if(*ptr >= 'a' && *ptr <= 'z')
	{
		int loc[2] = {(*ptr - 'a'), 0};

		if(*(ptr+1) != ' ')
			loc[1] = *(ptr+1) - 'a';
		
		if(!defined[loc[0]][loc[1]])
			return 0;

		*result = signals[loc[0]][loc[1]];
		return 1;
	}
	else
	{ // TODO: check this doesnt ever overflow
		*result = (u16) strtoul(ptr, NULL, 10);
		return 1;
	}
}

char parseLine(gate* g)
{
	g->eval = 0;
	char bufStr[10] = {0};
	char eofcheck = fscanf(fp, "%s", bufStr);
	if(eofcheck == EOF)
		return 0;
	if(bufStr[0] == 'N')
	{// this is a NOT line
		g->inst = NOT;
		fscanf(fp, "%s", bufStr); // read in the symbol
		parseSymbol(g, 1, bufStr); //parse it
		fscanf(fp, "%s", bufStr); // should read an arrow
		fscanf(fp, "%s", bufStr); // should read the output symbol which is guaranteed to be a signal
		parseSymbol(g, 3, bufStr);
		return 1;
	}
	// otherwise it starts with a symbol
	// bufStr currently represents a symbol
	parseSymbol(g, 1, bufStr);
	fscanf(fp, "%s", bufStr);
	//bufStr now is showing an operator or a (->)
	if(bufStr[0] == '-')
	{// this is a basic assign operation
		g->inst = ASSIGN;
		fscanf(fp, "%s", bufStr);
		parseSymbol(g, 3, bufStr);
		return 1;
	}
	// otherwise bufStr is now pointing at an operator
	switch(bufStr[0])
	{
	case('O'):
		g->inst = OR;
		break;
	case('A'):
		g->inst = AND;
		break;
	case('R'):
		g->inst = RSHIFT;
		break;
	case('L'):
		g->inst = LSHIFT;
		break;
	default:
		printf("fell through to bottom case in switch: %c", bufStr[0]);
	}
	fscanf(fp, "%s", bufStr);
	parseSymbol(g, 2, bufStr);
	fscanf(fp, "%s", bufStr); // should read a (->)
	fscanf(fp, "%s", bufStr); // should read the output location
	parseSymbol(g, 3, bufStr);
	return 1;
}

void parseSymbol(gate *g, int num, char* str)
{
	if(num == 1)
	{
		if(str[0] >= 'a' && str[0] <= 'z')
		{ // signal
			g->const1 = 0;
			g->in1[0] = str[0] - 'a';
			if(str[1] == ' ' || str[1] == 0)
				g->in1[1] = 26;
			else
				g->in1[1] = str[1] - 'a';
		}
		else
		{ // literal
			g->const1 = 1;
			g->val1 = (u16) strtoul(str, NULL, 10);
		}
	}
	else if(num == 2)
	{
		if(str[0] >= 'a' && str[0] <= 'z')
		{ // signal
			g->const2 = 0;
			g->in2[0] = str[0] - 'a';
			if(str[1] == ' ' || str[1] == 0)
				g->in2[1] = 26;
			else
				g->in2[1] = str[1] - 'a';
		}
		else
		{ // literal
			g->const2 = 1;
			g->val2 = (u16) strtoul(str, NULL, 10);
		}
	}
	else if(num == 3)
	{
		if(str[0] >= 'a' && str[0] <= 'z')
		{ // signal
			g->out[0] = str[0] - 'a';
			if(str[1] == ' ' || str[1] == 0)
				g->out[1] = 26;
			else
				g->out[1] = str[1] - 'a';
		}
		else
		{ // literal
			printf("ERROR: tried to parse a literal as an output (%d)"
			       "undefined behaviour now occurs\n", num);
		}
	}
	else
	{
		printf("ERROR: illegal num passed to parseSymbol() (%d) "
		       "(undefined behaviour will now occur)\n", num);
	}
}

void printGate(gate *g)
{
	if(g->inst == NOT)
	{
		printf("NOT ");
		printSymbol(g, 1);
		printf("-> ");
		printSymbol(g, 3);
		printf("\n");
		return;
	}
	else if(g->inst == ASSIGN)
	{
		printSymbol(g, 1);
		printf("-> ");
		printSymbol(g, 3);
		printf("\n");
	}
	else
	{
		printSymbol(g, 1);
		switch(g->inst)
		{
		case(OR):
			printf("OR ");
			break;
		case(AND):
			printf("AND ");
			break;
		case(LSHIFT):
			printf("LSHIFT ");
			break;
		case(RSHIFT):
			printf("RSHIFT ");
			break;
		default: //unreachable, this just silences the not all handled error
			break;
		}
		printSymbol(g, 2);
		printf("-> ");
		printSymbol(g, 3);
		printf("\n");
	}
}

void printSymbol(gate *g, int num)
{
	switch(num)
	{
	case(1):
		if(g->const1)
		{
			printf("%d ", g->val1);
		}
		else
		{
			printf("%c", g->in1[0]+'a');
			if(g->in1[1] == 26)
				printf("  ");
			else
				printf("%c ", g->in1[1]+'a');
		}
		break;
	case(2):
		if(g->const2)
		{
			printf("%d ", g->val2);
		}
		else
		{
			printf("%c", g->in2[0]+'a');
			if(g->in2[1] == 26)
				printf("  ");
			else
				printf("%c ", g->in2[1]+'a');
		}
		break;
	case(3):
		printf("%c", g->out[0]+'a');
		if(g->out[1] == 26)
			printf("  ");
		else
			printf("%c ", g->out[1]+'a');
		break;
	default:
		printf("wrong num passed to printsymbol (%d)\n", num);
	}
}
