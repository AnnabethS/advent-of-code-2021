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
	u16 assign; //const input used for basic ASSIGN operations
	enum op inst; //the operation this gate performs
	int out[2]; //the location the output should be put
	char eval; //1 if this gate HAS been evaluated, 0 otherwise
}gate;

/* the first index is the first letter of the signal name
the second is the second letter, unless its ' ' which is
stored at index 26 */
u16 signals[26][27] = {0};
char defined[26][27] = {0};
gate gates[340] = {0};
FILE* fp;

// forward function definitions

/*
  Parses a single symbol, either a signal like "wq" or a literal 
Returns 0 when symbol cannot be evaluated because its undefined
otherwise returns 1
 */
char parseSymbol(char* ptr, u16* result);

// Returns 1 if both input signals are defined, 0 otherwise
char checkValidInputs(gate* g);

//parses a line of input, and adds the gate to the gates list
void parseLine(gate* g);

int main()
{
	fp = fopen("input.txt", "r");
}

/*
  attempts to evaluate a gate, returns 0 if not evaulated,
  returns 1 if correctly evaluated
 */
char evalGate(gate* g)
{
	switch(g->inst)
	{
	case(OR):
		if(!checkValidInputs(g))
			return 0;
		signals[g->out[0]][g->out[1]] = signals[g->in1[0]][g->in1[1]] | signals[g->in2[0]][g->in2[1]];
		defined[g->out[0]][g->out[1]] = 1;
		return 1;
	case(AND):
		if(!checkValidInputs(g))
			return 0;
		signals[g->out[0]][g->out[1]] = signals[g->in1[0]][g->in1[1]] & signals[g->in2[0]][g->in2[1]];
		defined[g->out[0]][g->out[1]] = 1;
		return 1;
	case(RSHIFT):
		if(!checkValidInputs(g))
			return 0;
		signals[g->out[0]][g->out[1]] = signals[g->in1[0]][g->in1[1]] >> signals[g->in2[0]][g->in2[1]];
		defined[g->out[0]][g->out[1]] = 1;
		return 1;
	case(LSHIFT):
		if(!checkValidInputs(g))
			return 0;
		signals[g->out[0]][g->out[1]] = signals[g->in1[0]][g->in1[1]] << signals[g->in2[0]][g->in2[1]];
		defined[g->out[0]][g->out[1]] = 1;
		return 1;
	case(NOT):
		if(!(defined[g->in1[0]][g->in1[1]]))
			return 0;
		signals[g->out[0]][g->out[1]] = ~ signals[g->in1[0]][g->in1[1]];
		defined[g->out[0]][g->out[1]] = 1;
		return 1;
	case(ASSIGN):
		signals[g->out[0]][g->out[1]] = g->assign;
		defined[g->out[0]][g->out[1]] = 1;
		return 1;
	}
}

char checkValidInputs(gate* g)
{
	return defined[g->in1[0]][g->in1[1]] && defined[g->in2[0]][g->in2[1]];
		
}

char parseSymbol(char* ptr, u16* result)
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

void parseLine(gate* g)
{
	char bufStr[10] = {0};
	fscanf(fp, "%s", bufStr);
	if(bufStr[0] == 'N')
	{// this is a NOT line
		g->inst = NOT;
		fscanf(fp, "%s", bufStr);

	}
	// otherwise it starts with a symbol
}
