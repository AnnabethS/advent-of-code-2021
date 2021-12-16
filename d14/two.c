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

char getRule(char c1, char c2, rule rules[RULEAMOUNT]);
char doStep(long long *pairs, long long occurances[26], rule rules[RULEAMOUNT]);

void printPairs(long long *pairs);

int main()
{
    FILE* fp = fopen(FILENAME, "r");
    char bufStr[MAXBUFLEN] = {'\0'};

    
    fscanf(fp, "%s", bufStr);
    rule rules[RULEAMOUNT];

    fscanf(fp, "%s", (char*) NULL);
    for(int i=0; i < RULEAMOUNT; i++)
    {
        fscanf(fp, "%c%c -> %c\n", &rules[i].from[0], &rules[i].from[1], &rules[i].ins);
    }
    long long occurances[26] = {0};
        
    for(int i=0; i < 26; i++)
    {
        for (int j=0; j < MAXBUFLEN; j++)
        {
            if(bufStr[j] == (i + 'A'))
                occurances[i]++;
        }
    }

    /* for (int i=0; i < 26; i++) */
    /* { */
        /* printf("%c -> %ld\n", i+'A', occurances[i]); */
    /* } */
    
    long long *pairs = (long long *) calloc(sizeof(long long)*26, 26);
    
    /* printPairs(pairs); */

    /* printf("%lld\n", *(pairs + ())); */

    for(int i=0; bufStr[i+1] != '\0'; i++)
    {
        char x1 = bufStr[i] - 'A';
        char x2 = bufStr[i+1] - 'A';
        /* printf("compare %c (%d) - %c (%d)\n", bufStr[i], x1, bufStr[i+1], x2); */
        *(pairs + (x1*26) + x2) = *(pairs + (x1*26) + x2) + 1;
    }
    
    /* printPairs(pairs); */
    for(int i=0; i < 40; i++)
        doStep(pairs, occurances, rules);

    /* for (int i=0; i < 26; i++) */
    /* { */
        /* printf("%c -> %ld\n", i+'A', occurances[i]); */
    /* } */
    long long maxOccurances = 0;
    long long minOccurances = LLONG_MAX;

    for(int i=0; i < 26; i++)
    {
        if(occurances[i] > maxOccurances)
            maxOccurances = occurances[i];
        if(occurances[i] > 0 && occurances[i] < minOccurances)
            minOccurances = occurances[i];
    }
    printf("max %lld min %lld\n", maxOccurances, minOccurances);
    
    long long output = maxOccurances - minOccurances;
    printf("output: %lld\n", output);
}

char doStep(long long *pairs, long long occurances[26], rule rules[RULEAMOUNT])
{
    long long *newPairs = calloc(sizeof(long long)*26, 26);
    newPairs = memcpy(newPairs, pairs, sizeof(long long)*26*26);
    for(int c1=0; c1 < 26; c1++)
    {
        for(int c2=0; c2 < 26; c2++)
        {
            char r = getRule('A' + c1, 'A' + c2, rules);
            if(r != 0)
            {
                long long amountPairs = *(pairs + (c1*26) + c2);
                *(newPairs + (c1*26) + c2) -= amountPairs;
                *(newPairs + (c1*26) + r) += amountPairs;
                *(newPairs + (r*26) + c2) += amountPairs;
                occurances[r] += amountPairs;
            }
        }
    }
    memcpy(pairs, newPairs, sizeof(long long)*26*26);
    return 0;
}

char getRule(char c1, char c2, rule rules[RULEAMOUNT])
{
    for(int i=0; i < RULEAMOUNT; i++)
    {
        if(c1==rules[i].from[0] && c2 == rules[i].from[1])
            return (rules[i].ins) - 'A';
    }
    return 0;
}

void printPairs(long long *pairs)
{
    printf("col -> row\n  ");
    for(int i=0; i < 26; i++)
    {
        printf("%4c|", i+'A');
    }
    printf("\n");
    for (int i=0; i < 26; i++)
    {
        printf("%c ", i+'A');
        for(int j=0; j < 26; j++)
        {
            printf("%4lld|", *(pairs + (i*26) + j));
        }
        printf("\n");
        for(int j=0; j <= 26*5; j++)
        {
            printf("-");
        }
        printf("\n");
    }
    printf("\n");
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
