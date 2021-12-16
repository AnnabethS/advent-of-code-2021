#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#ifdef TEST
#define FILENAME "test.txt"
#define INPUTDIMX 10
#define INPUTDIMY 10

#else

#define FILENAME "input.txt"
#define INPUTDIMX 100
#define INPUTDIMY 100

#endif

#define MAXHEAPSIZE 25000

typedef struct node{
    int x;
    int y;
    int g;
    double h;
    double f;
}node;

long DIMY = 500;
long DIMX = 500;

void getCosts(node *n, node *prevNode, int cost[DIMY][DIMX]);
void printNode(node *n);
void getSuccessors(node *n, node outNodes[4], int cost[DIMY][DIMX]);
void insertIntoHeap(node heap[MAXHEAPSIZE], long *lastHeapObject, node x);
void swapNode(node* n1, node* n2);
long getParent(long i);
long getRightChild(long i);
long getLeftChild(long i);
void fixHeap(node heap[MAXHEAPSIZE], long i, long lastHeapObject);
node extractMin(node heap[MAXHEAPSIZE], long *lastHeapObject);
void printHeap(node heap[MAXHEAPSIZE], long lastHeapObject);

int main(void)
{
    printf("test\n");
    printf("size of node: %ld\n", sizeof(node));
    FILE* fp = fopen(FILENAME, "r");
    
    int cost[DIMY][DIMX];

    for(int y=0; y < INPUTDIMY; y++)
    {
        for(int x=0; x < INPUTDIMX; x++)
        {
            char bufChar;
            fscanf(fp, "%c", &bufChar);
            cost[y][x] = bufChar - '0';
        }
        char buf2;
        fscanf(fp, "%c", &buf2);
    }

    fclose(fp);

    for(int tileY=0; tileY < 5; tileY++)
    {
        for(int tileX=0; tileX < 5; tileX++)
        {
            for(int y=0; y < INPUTDIMY; y++)
            {
                for(int x=0; x < INPUTDIMX; x++)
                {
                    int newval = cost[y][x]+tileX + tileY;
                    if(newval>9)
                        newval = newval - 9;
                    cost[tileY*INPUTDIMY + y][tileX*INPUTDIMX + x] = newval;
                }
            }
        }
    }
    printf("big grid created\nsolving path...\n");

    /* node heap[INT_MAX]; */
    node* heap = calloc(MAXHEAPSIZE, sizeof(node));
    long lastHeapObject = 0;
    /* memset(heap, -1, sizeof(node)*DIMX*DIMY); */
    heap[0].x = 0;
    heap[0].y = 0;
    heap[0].g = 0;
    heap[0].f = 0;
    getCosts(&heap[0], &heap[0], cost);

    printHeap(heap, lastHeapObject);
    
    double closed[DIMY][DIMX];
    for(long y=0; y < DIMY; y++)
    {
        for(long x=0; x < DIMX; x++)
        {
            closed[y][x] = -1;
        }
    }
    printf("here\n");
    
    node currNode;
    char goalFound = 0;
    while(!goalFound)
    {
        /* printHeap(heap, lastHeapObject); */
        currNode = extractMin(heap, &lastHeapObject);
        /* printf("\n"); */
        /* printNode(&currNode); */
        /* printf("neighbours\n"); */
        closed[currNode.y][currNode.x] = currNode.f;
        node neighbours[4];
        getSuccessors(&currNode, neighbours, cost);
        for(int i=0; i < 4; i++)
        {
            if(neighbours[i].x != -1)
            {
                /* printf(" "); */
                /* printNode(&neighbours[i]); */
                if(neighbours[i].x == DIMX-1 && neighbours[i].y == DIMY-1)
                {
                    printf("found the end\n");
                    goalFound = 1;
                    break;
                }
                if(closed[neighbours[i].y][neighbours[i].x] >= 0)
                {
                    continue;
                    if(closed[neighbours[i].y][neighbours[i].x] > neighbours[i].f)
                    {
                        /* printf("CLOSED REPLACED: %f\n", closed[neighbours[i].y][neighbours[i].x]); */
                        /* printf("WITH:\n"); */
                        /* printNode(&neighbours[i]); */
                        closed[currNode.y][currNode.x] = neighbours[i].f;
                        insertIntoHeap(heap, &lastHeapObject, neighbours[i]);
                        continue;
                    }
                    else
                    {
                        continue;
                    }
                }
                /* printf("insert: "); */
                /* printNode(&neighbours[i]); */
                insertIntoHeap(heap, &lastHeapObject, neighbours[i]);
            }
        }
    }

    node *ptr = &currNode;
    printf("final g cost: %d\n", currNode.g + cost[DIMY-1][DIMX-1]);
    /* long total = 0; */
    /* while(ptr->prev != NULL) */
    /* { */
    /*     printNode(ptr); */
    /*     ptr = ptr->prev; */
    /*     total += cost[ptr->y][ptr->x]; */
    /* } */
    /* printf("%ld\n", total); */

/*     for(int i=0; i < 50; i++) */
/*     { */
/*         for(int j=0; j < 50; j++) */
/*         { */
/*             printf("%3d ", closed[i][j].g); */
/*         } */
/*         printf("\n"); */
/*     } */
}

void insertIntoHeap(node heap[MAXHEAPSIZE], long *lastHeapObject, node x)
{
    if(*lastHeapObject == -1)
    {
        heap[0] = x;
        (*lastHeapObject)++;
        return;
    }
    if(*lastHeapObject >= MAXHEAPSIZE)
    {
        /* printf("heap size exceeded %ld\n", *lastHeapObject); */
        return;
    }
    heap[*lastHeapObject] = x;
    (*lastHeapObject)++;
    
    long i = (*lastHeapObject) - 1;
    while(i != 0 && heap[getParent(i)].f > heap[i].f)
    {
        swapNode(&heap[getParent(i)], &heap[i]);
        i = getParent(i);
    }
}

node extractMin(node heap[MAXHEAPSIZE], long *lastHeapObject)
{
    node min = heap[0];
    heap[0] = heap[*lastHeapObject - 1];
    (*lastHeapObject)--;

    fixHeap(heap, 0, *lastHeapObject);
    return min;
}

void printHeap(node heap[MAXHEAPSIZE], long lastHeapObject)
{
    printf("heap: \n");
    if(lastHeapObject == -1)
    {
        printf("nothing in the heap\n");
        return;
    }
    for(int i=0; i < lastHeapObject; i++)
    {
        printNode(&heap[i]);
    }
}

void fixHeap(node heap[MAXHEAPSIZE], long i, long lastHeapObject)
{
    long left = getLeftChild(i);
    long right = getRightChild(i);
    long smallest = i;

    if(left <= lastHeapObject && heap[left].f < heap[smallest].f)
        smallest = left;

    if(right <= lastHeapObject && heap[right].f < heap[smallest].f)
        smallest = right;

    if(smallest != i)
    {
        node tmp = heap[i];
        heap[i] = heap[smallest];
        heap[smallest] = tmp;
        fixHeap(heap, smallest, lastHeapObject);
    }
}

long getParent(long i)
{
    return (i - 1) / 2;
}

long getLeftChild(long i)
{
    return 2*i + 1;
}

long getRightChild(long i)
{
    return 2*i + 2;
}

void swapNode(node* n1, node* n2)
{
    node* tmp = malloc(sizeof(node));
    memcpy(tmp, n1, sizeof(node));
    memcpy(n1, n2, sizeof(node));
    memcpy(n2, tmp, sizeof(node));
    free(tmp);
}

void getCosts(node *n, node *prevNode, int cost[DIMY][DIMX])
{
    if(prevNode->g != -1)
        n->g = cost[n->y][n->x] + prevNode->g;
    else
    {
        n->g = 0;
        printf("-1 occured\n");
    }
        /* n->g = 0; */
    /* n->h = sqrt(pow((DIMX - 1 - n->x),2) + pow((DIMY - 1 - n->y),2)); */
    n->h = 0;
    n->f = n->g + n->h;
}

void getSuccessors(node *n, node outNodes[4], int cost[DIMY][DIMX])
{
    // intended shape
    //  0
    //3 N 1
    //  2 
    int dirs[4][2] = {{0,-1},{1,0},{0,1},{-1,0}};
    for(int i=0; i < 4; i++)
    {
        int x = n->x + dirs[i][0];
        int y = n->y + dirs[i][1];
        if(x >= 0 && x < DIMX && y >= 0 && y < DIMY)
        {
            outNodes[i].x = x;
            outNodes[i].y = y;
            getCosts(&outNodes[i], n, cost);
        }
        else
        {
            outNodes[i].x = -1;
            outNodes[i].f = -1;
        }
    }
}

void printNode(node *n)
{
    printf("x: %d, y: %d, g: %d, f: %f\n", n->x, n->y, n->g, n->f);
}
