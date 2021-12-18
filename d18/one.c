#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifdef TEST
#define FILENAME "test.txt"
#define LINES 10
#else
#define FILENAME "input.txt"
#define LINES 2
#endif

#define BUFLEN 200

typedef struct pair{
    struct pair *upPair;
    struct pair *leftPair;
    struct pair *rightPair;
    int leftNum;
    int rightNum;
}pair;

//pair operations
void addPair(pair **dest, pair *leftPair, pair *rightPair);
void initPair(pair *p);
void splitPair(pair *p, char side);
void explodePair(pair *p);
char checkForSplits(pair *p);
char reducePair(pair *p);
int checkForExplosion(pair *p, int depth);

//input
void parseInputString(pair **topPair, char **str);

//debug
void printPair(pair *top);

int main() {
    pair *top;
    char *testStr = calloc(62, sizeof(char));
    char *ptr = testStr;
/*     strcpy(testStr, "[[[[[4,3],4],4],[7,[[8,4],9]]],[1,1]]"); */
/*     parseInputString(&top, &ptr); */

/*     printf("input:"); */
/*     printPair(top); */
/*     printf("\n"); */

/*     reducePair(top); */

/*     printPair(top); */
/*     printf("\n"); */
    char bufStr[BUFLEN] = {'\0'};
    char *inp_ptr = &bufStr[0]; 
    pair *inputPairs[LINES];
    FILE* fp = fopen(FILENAME, "r");
    for(int i=0; i < LINES; i++)
    {
        inp_ptr = &bufStr[0];
        fscanf(fp, "%s", bufStr);
        parseInputString(&inputPairs[i], &inp_ptr);
    /*     printPair(inputPairs[i]); */
    /*     printf("\n"); */
    }

    pair *currTotal;
    addPair(&currTotal, inputPairs[0], inputPairs[1]);
    printPair(currTotal);
    printf("\n");
    reducePair(currTotal);
    printPair(currTotal);

}

//will complete 0 or 1 operations, returning amount of operations performed
char reducePair(pair *p)
{
    while(1) // check for explosions
    {
        printPair(p);
        printf("\n");
        /* printf("reduce\n"); */
        if(checkForExplosion(p, 0))
            continue;
    
        if(checkForSplits(p))
            continue;

        /* printPair(p);printf("\n"); */
        break;
    }
    return 0;
}

int checkForExplosion(pair *p, int depth)
{
    printf("checking pair: ");printPair(p);
    printf("\ndepth: %d\n", depth);
    if(depth >= 4)
    {// too deep! we must explode the number
        /* printf("found explosion\n"); */
        explodePair(p);
        return 1;
    }
    if(p->leftNum == -1)
    {
        if(checkForExplosion(p->leftPair, depth+1))
        { //somewhere down the recursion, something exploded, return
            return 1;
        }
    }
    if(p->rightNum == -1)
    {
        if(checkForExplosion(p->rightPair, depth+1))
        {
            return 1;
        }
    }
    return 0;
}

//return 0 on no split done, return 1 on split done
char checkForSplits(pair *p)
{
    if(p->leftNum != -1)
    {
        if(p->leftNum >= 10)
        {
            splitPair(p, 'L');
            return 1;
        }
    }
    else if(checkForSplits(p->leftPair))
    {
        return 1;
    }

    if(p->rightNum != -1)
    {
        if(p->rightNum >= 10)
        {
            splitPair(p, 'R');
            return 1;
        }
    }
    else if(checkForSplits(p->rightPair))
    {
        return 1;
    }
    return 0;
}

void splitPair(pair *p, char side)
{
    int *num;
    pair *newLoc;
    if(side == 'L')
    {
        num = &(p->leftNum);
        newLoc = malloc(sizeof(pair));
        initPair(newLoc);
        p->leftPair = newLoc;
    }
    else if (side == 'R')
    {
        num = &(p->rightNum);
        newLoc = malloc(sizeof(pair));
        initPair(newLoc);
        p->rightPair = newLoc;
    }
    else
    {
        printf("ERROR: invalid input to splitPair: side = %c,"
               " must be 'L' or 'R'\n", side);
        return;
    }

    if(*num == -1)
    {
        printf("tried to split a non-literal number, side = %c, pair:\n", side);
        printPair(p);
    }

    if(*num <= 9)
    {
        printf("tried to split a number which doesnt need splitting,"
               "side = %c, pair:\n", side);
        printPair(p);
    }

    float left = floor((float)*num / 2);
    float right = ceil((float)*num / 2);

    newLoc->leftNum = (int)left;
    newLoc->rightNum = (int)right;

    newLoc->upPair = p;

    *num = -1;
}

void explodePair(pair *p)
{
    pair *parent_ptr = p->upPair;
    pair *ptr = p;

    /* printf("exploding pair: "); */
    /* printPair(p); */
    /* printf("\n"); */
    
    /* if(parent_ptr == NULL)
         return; */
    /* printf("parent ptr: %d", parent_ptr==NULL); */
    
    if(parent_ptr->rightPair == ptr)
    {
        /* printf("left symbol, right pair\n"); */
        // the parent pair has the current pair on the right, therefore there is
        // a left symbol we can add to, somewhere down the left tree
        pair *rightmost = parent_ptr;
        while(rightmost->leftPair != NULL)
        {
            /* printf("check:\n"); */
            /* printPair(rightmost);printf("\n"); */
            rightmost = rightmost->leftPair;
        }
        // we have found the pair with the rightmost literal
        rightmost->leftNum += p->leftNum;
    }
    else if(parent_ptr->leftPair == ptr)
    { //seems to be working
        printf("left symbol, left pair\n");
        pair *rightmost = parent_ptr;
        while(rightmost->upPair != NULL)
        {
            /* printPair(rightmost); */
            /* printf("\n"); */
            if(rightmost->upPair->rightPair == rightmost)
            {// there is now a number / pair on the right.
                /* printf("here\n"); */
                rightmost = rightmost->upPair;
                /* printf("rightmost: ");printPair(rightmost);printf("\n"); */
                if(rightmost->leftPair == NULL)
                { // there is a number immidiatly left
                    /* printf("number found...\n"); */
                    rightmost->leftNum += p->leftNum;
                    break;
                }
                rightmost = rightmost->leftPair;
                while(rightmost->rightNum == -1)
                {
                    /* printPair(rightmost); */
                    /* printf("\n"); */
                    rightmost = rightmost->rightPair;
                }
                rightmost->rightNum += p->leftNum;
                break;
            }
            rightmost = rightmost->upPair;
        }
    }
    else
    {
        printf("unreachable\n");
    }

    /* printPair(p);printf("\n"); */

    /* printf("done left num check\n"); */

    if(parent_ptr->leftPair == ptr)
    {
        printf("right symbol, left pair\n");
        // the parent pair has the current pair on the left, therefore there is
        // a right symbol we can add to, somewhere down the right tree
        pair *leftmost = parent_ptr;
        if(leftmost->rightPair == NULL)
        { // there is a number immidiatly right
            leftmost->rightNum += p->rightNum;
        }
        else
        {
            leftmost = leftmost->rightPair;
            while(leftmost != NULL)
            {
                if(leftmost->leftPair == NULL)
                {
                    leftmost->leftNum += p->rightNum;
                }
                leftmost = leftmost->leftPair;
            }
        }
    }
    else if(parent_ptr->rightPair == ptr)
    { // the pair is on the right, we care about the right number
        /* printf("right symbol, right pair\n"); */
        pair *leftmost = ptr;
        while(leftmost != NULL)
        {
            /* printPair(leftmost); */
            /* printf("\n"); */
            if(leftmost->upPair->leftPair == leftmost)
            {// there is now a number / pair on the right.
                /* printf("here\n"); */
                leftmost = leftmost->upPair;
                /* printf("leftmost: ");printPair(leftmost);printf("\n"); */
                if(leftmost->leftPair == NULL)
                { // there is a number immidiatly right
                    leftmost->leftNum += p->rightNum;
                    break;
                }
                leftmost = leftmost->leftPair;
                while(leftmost->leftNum == -1)
                {
                    /* printPair(leftmost); */
                    /* printf("\n"); */
                    leftmost = leftmost->leftPair;
                }
                leftmost->leftNum += p->leftNum;
                break;
            }
            leftmost = leftmost->upPair;
        }
    }

    // we have added where we needed to, sort out parent pair
    if(parent_ptr->leftPair == p)
    {
        parent_ptr->leftNum = 0;
        free(parent_ptr->leftPair);
        parent_ptr->leftPair = NULL;
    }
    else if(parent_ptr->rightPair == p)
    {
        parent_ptr->rightNum = 0;
        free(parent_ptr->rightPair);
        parent_ptr->rightPair = NULL;
    }
}

// str should point to the opening [ of a pair that needs parsing
void parseInputString(pair **topPair, char **str)
{
    if(**str != '[')
    {
        printf("illegal string parse!");
        return;
    }
    *topPair = malloc(sizeof(pair));
    initPair(*topPair);
    (*str)++;
    if(**str == '[')
    { // its another nested pair
        parseInputString(&((*topPair)->leftPair), str);
        (*topPair)->leftPair->upPair = *topPair;
        (*str)++;
    }
    else if (**str >= '0' && **str <= '9')
    { // literal number
        (*topPair)->leftNum = **str - '0';
    }
    else
    { // illegal input.
        printf("illegal input during left parse. (%c) detected\n", **str);
        return;
    }

    (*str)++;
    (*str)++;

    if(**str == '[')
    { // its another nested pair
        parseInputString(&((*topPair)->rightPair), str);
        (*topPair)->rightPair->upPair = *topPair;
        (*str)++;
    }
    else if (**str >= '0' && **str <= '9')
    { // literal number
        (*topPair)->rightNum = **str - '0';
    }
    else
    { // illegal input.
        printf("illegal input during right parse. (%c) detected\n", **str);
        return;
    }
}

void initPair(pair *p)
{
    p->upPair = NULL;
    p->leftPair = NULL;
    p->rightPair = NULL;
    p->leftNum = -1;
    p->rightNum = -1;
}

void addPair(pair **dest, pair *leftPair, pair *rightPair)
{
    *dest = malloc(sizeof(pair));
    initPair(*dest);
    (*dest)->leftPair = leftPair;
    leftPair->upPair = *dest;
    (*dest)->rightPair = rightPair;
    rightPair->upPair = *dest;
}

void printPair(pair *top)
{
    printf("[");

    if(top->leftNum == -1)
        printPair(top->leftPair);
    else
        printf("%d", top->leftNum);

    printf(",");

    if(top->rightNum == -1)
        printPair(top->rightPair);
    else
        printf("%d", top->rightNum);

    printf("]");
}
