#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#ifdef TEST
#define FILENAME "test.txt"
#define MAXBUFLEN 8
#define POLYSTRINGLEN 2000
#define RULEAMOUNT 16
#else
#define FILENAME "input.txt"
#define MAXBUFLEN 20
#define POLYSTRINGLEN 2000
#define RULEAMOUNT 100
#endif

typedef struct rule
{
    char from[2];
    char ins;
}rule;

void printRule(rule *r);
void printAllRules(rule r[RULEAMOUNT]);

char doStep(char **polyStart_ptr, int *currSize, rule rules[RULEAMOUNT]);

int main()
{
    FILE* fp = fopen(FILENAME, "r");
    char bufStr[MAXBUFLEN] = {'\0'};

    char *polyStart = calloc(sizeof(char), POLYSTRINGLEN);
    
    fscanf(fp, "%s", bufStr);
    strcpy(polyStart, bufStr);
    rule rules[RULEAMOUNT];

    fscanf(fp, "%s", (char*) NULL);
    for(int i=0; i < RULEAMOUNT; i++)
    {
        fscanf(fp, "%c%c -> %c\n", &rules[i].from[0], &rules[i].from[1], &rules[i].ins);
    }

    int currSize = POLYSTRINGLEN;
    for (int i=0; i < 10; i++)
    {
        char x = doStep(&polyStart, &currSize, rules);
        if (x == -1)
            break;
    }

    int occurances[26] = {0};
    char *ptr = polyStart;
    while(*ptr != '\0')
    {
        occurances[*ptr - 'A']++;
        ptr++;
    }
        
    int maxOccurances = 0;
    int minOccurances = INT_MAX;

    for(int i=0; i < 26; i++)
    {
        if(occurances[i] > maxOccurances)
            maxOccurances = occurances[i];
        if(occurances[i] != 0 && occurances[i] < minOccurances)
            minOccurances = occurances[i];
    }

    int output = maxOccurances - minOccurances;
    printf("output: %d\n", output);
}

char doStep(char **polyStart_ptr, int *currSize, rule rules[RULEAMOUNT])
{
    char *polyBackStart = calloc(sizeof(char), *currSize);
    // points at the current char being evaluated
    char* poly_ptr = *polyStart_ptr;
    //points at the next free spot of polyBack
    char* polyBack_ptr = polyBackStart;
    /* printf("%s\n\n", *polyStart_ptr); */
    while(*(poly_ptr+1) != '\0')
    {
        *polyBack_ptr = *poly_ptr;
        polyBack_ptr++;
        for(int i=0; i < RULEAMOUNT; i++)
        {
            if(*poly_ptr == rules[i].from[0] && *(poly_ptr + 1) == rules[i].from[1])
            {
                *polyBack_ptr = rules[i].ins;
                polyBack_ptr++;
                break;
            }
        }
        poly_ptr++;
        if(polyBack_ptr - polyBackStart >= *currSize - 2)
        { // we will overflow on the next addition, so allocate more memory
            char *oldPolyBackStart = polyBackStart;
            polyBackStart = reallocarray(polyBackStart, (*currSize)*2, sizeof(char));
            polyBack_ptr = polyBackStart + (polyBack_ptr - oldPolyBackStart);

            char *oldPolyStart = *polyStart_ptr;
            *polyStart_ptr = reallocarray(*polyStart_ptr, (*currSize)*2, sizeof(char));
            poly_ptr = *polyStart_ptr + (poly_ptr - oldPolyStart);
            
            *currSize *= 2;
            printf("overflow prevented, currsize: %d \n", *currSize);
        }
        if(polyBack_ptr - polyBackStart >= *currSize)
        {
            printf("fail: overflowed anyway :(\n");
            return -1;
        }

    }
    *polyBack_ptr = *poly_ptr;
    polyBack_ptr++;
    *polyBack_ptr = '\0';
    strcpy(*polyStart_ptr, polyBackStart);
    free(polyBackStart);
    return 0;
}

void printRule(rule *r)
{
    printf("%c%c -> %c\n", r->from[0], r->from[1], r->ins);
}

void printAllRules(rule r[RULEAMOUNT])
{
    for(int i=0; i < RULEAMOUNT; i++)
    {
        printRule(&r[i]);
    }
}
