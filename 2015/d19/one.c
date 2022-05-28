#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HASH_TABLE_SIZE 10000
#define REPLACEMENT_AMOUNT 43

struct replacement{
	char* from;
	char* to;
};

char* input_molecule = "CRnCaCaCaSiRnBPTiMgArSiRnSiRnMgArSiRnCaFArTiTiBSiThFYCaFArCaCaSiThCaPBSiThSiThCaCaPTiRnPBSiThRnFArArCaCaSiThCaSiThSiRnMgArCaPTiBPRnFArSiThCaSiRnFArBCaSiRnCaPRnFArPMgYCaFArCaPTiTiTiBPBSiThCaPTiBPBSiRnFArBPBSiRnCaFArBPRnSiRnFArRnSiRnBFArCaFArCaCaCaSiThSiThCaCaPBPTiTiRnFArCaPTiBSiAlArPBCaCaCaCaCaSiRnMgArCaSiThFArThCaSiThCaSiRnCaFYCaSiRnFYFArFArCaSiRnFYFArCaSiRnBPMgArSiThPRnFArCaSiRnFArTiRnSiRnFYFArCaSiRnBFArCaSiRnTiMgArSiThCaSiThCaFArPRnFArSiRnFArTiTiTiTiBCaCaSiRnCaCaFYFArSiThCaPTiBPTiBCaSiThSiRnMgArCaF";

char** hash_table;

struct replacement rps[REPLACEMENT_AMOUNT] = {0};

void init_replacement(struct replacement* dst, char* from, char* to);

// sourced from this website: http://www.cse.yorku.ca/~oz/hash.html
unsigned long hash(unsigned char *str)
{
	unsigned long hash = 5381;
	int c;

	while (c = *str++)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash;
}

// strcmp(a,b) >> -1 means a is alphabetically before b
// strcmp(a,b) >> 0 means a is the same as b
// strcmp(a,b) >> 1 means a is alphabetically after b

int main()
{
	hash_table = calloc(HASH_TABLE_SIZE, sizeof(char*));
	// parse replacements
	FILE* fp = fopen("input.txt", "r");

	char from_buffer[3] = {0};
	char to_buffer[10] = {0};

	for(int i=0; i < REPLACEMENT_AMOUNT; i++)
	{
		fscanf(fp, "%s => %s\n", from_buffer, to_buffer);
		init_replacement(&rps[i], from_buffer, to_buffer);
	}
}

void init_replacement(struct replacement* dst, char* from, char* to)
{
	dst->from = calloc(strlen(from)+1, sizeof(char));
	dst->to = calloc(strlen(to)+1, sizeof(char));
	strcpy(dst->from, from);
	strcpy(dst->to, to);
}
