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

#define MAXHEAPSIZE 50000000

typedef struct node{
    int x;
    int y;
    int g;
    double h;
    double f;
    int prevX;
    int prevY;
}node;

long DIMY = INPUTDIMY*5;
long DIMX = INPUTDIMX*5;

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
    if(heap == NULL)
        printf("calloc failed\n");
    long lastHeapObject = -1;
    /* memset(heap, -1, sizeof(node)*DIMX*DIMY); */
    heap[0].x = 0;
    heap[0].y = 0;
    heap[0].g = 0;
    heap[0].f = 0;
    getCosts(&heap[0], &heap[0], cost);
    node startNode;
    startNode.x = 0;
    startNode.y = 0;
    startNode.g = 0;
    startNode.f = 0;

    
    node *closed = calloc(DIMY*DIMX, sizeof(node));
    for(long y=0; y < DIMY; y++)
    {
        for(long x=0; x < DIMX; x++)
        {
            closed[DIMY*y + x].x = -1;
        }
    }
    
    node *open = calloc(DIMY*DIMX, sizeof(node));
    for(long y=0; y < DIMY; y++)
    {
        for(long x=0; x < DIMX; x++)
        {
            open[DIMY*y + x].x = -1;
        }
    }

    insertIntoHeap(heap, &lastHeapObject, startNode);

    node currNode;
    char goalFound = 0;
    while(!goalFound)
    {
        currNode = extractMin(heap, &lastHeapObject);
        while(currNode.f > closed[DIMY * currNode.y + currNode.x].f &&
              closed[DIMY * currNode.y + currNode.x].x != -1)
        {
            open[DIMY*currNode.y + currNode.x].x = -1;
            currNode = extractMin(heap, &lastHeapObject);
        }
        printf("node: ");
        printNode(&currNode);
        memcpy(&closed[DIMY*currNode.y + currNode.x], &currNode, sizeof(node));
        open[DIMY*currNode.y + currNode.x].x = -1;
        node neighbours[4];
        getSuccessors(&currNode, neighbours, cost);
        for(int i=0; i < 4; i++)
        {
            if(neighbours[i].x != -1)
            {
                if(neighbours[i].x == DIMX-1 && neighbours[i].y == DIMY-1)
                {
                    printf("found the end\n");
                    goalFound = 1;
                    break;
                }
                if(closed[DIMY * neighbours[i].y + neighbours[i].x].x != -1)
                {
                    continue;
                    if(closed[DIMY * neighbours[i].y + neighbours[i].x].f > neighbours[i].f)
                    {
                        closed[DIMY * currNode.y + currNode.x] = neighbours[i];
                        insertIntoHeap(heap, &lastHeapObject, neighbours[i]);
                        continue;
                    }
                    else
                    {
                        continue;
                    }
                }
                if(open[DIMY*neighbours[i].y + neighbours[i].x].x != 1 &&
                    open[DIMY*neighbours[i].y + neighbours[i].x].f > neighbours[i].f)
                {
                    char found=0;
                    for(int i=0; i < lastHeapObject; i++)
                    {
                        if(heap[i].x == neighbours[i].x && heap[i].y == neighbours[i].y)
                        {
                            printHeap(heap, lastHeapObject);
                            printf("removing: ");printNode(&neighbours[i]);
                            memcpy(&heap[i], &heap[lastHeapObject], sizeof(node));
                            lastHeapObject--;
                            fixHeap(heap, 0, lastHeapObject);
                            printHeap(heap, lastHeapObject);
                            found=1;
                            break;
                        }
                    }
                    if(!found)
                    {
                        printf("ERROR: couldnt remove from heap\n");
                        printHeap(heap, lastHeapObject);
                        printf("Enode: ");printNode(&neighbours[i]);
                    }
                    insertIntoHeap(heap, &lastHeapObject, neighbours[i]);
                    memcpy(&open[DIMY*neighbours[i].y + neighbours[i].x], &neighbours[i], sizeof(node));
                }
                else if(open[DIMY*neighbours[i].y + neighbours[i].x].x != -1)
                {
                    insertIntoHeap(heap, &lastHeapObject, neighbours[i]);
                    memcpy(&open[DIMY*neighbours[i].y + neighbours[i].x], &neighbours[i], sizeof(node));
                }
            }
        }
    }

    node *ptr = &currNode;

    printf("final route:\n");
    while(ptr->x != 0 || ptr->y != 0)
    {
        printf("%d %d : %d\n", ptr->x, ptr->y, ptr->g);
        ptr = &closed[DIMY * ptr->prevY + ptr->prevX];
    }
    


    printf("final g cost: %d\n", currNode.g + cost[DIMY-1][DIMX-1]);
}

void insertIntoHeap(node heap[MAXHEAPSIZE], long *lastHeapObject, node x)
{
    if(*lastHeapObject == -1)
    {
        heap[0] = x;
        /* lowIndex[DIMY*x.y + x.x] = 0; */
        (*lastHeapObject)++;
        return;
    }
    if(*lastHeapObject >= MAXHEAPSIZE)
    {
        printf("heap size exceeded %ld at node:\n", *lastHeapObject);
        printNode(&x);
        return;
    }
    heap[*lastHeapObject] = x;
    /* lowIndex[DIMY*x.y + x.x] = *lastHeapObject; */

    (*lastHeapObject)++;
    long i = (*lastHeapObject) - 1;
    while(i != 0 && heap[getParent(i)].f > heap[i].f)
    {
        swapNode(&heap[getParent(i)], &heap[i]);
        i = getParent(i);
        /* long tmpIndex = lowIndex[DIMY*heap[i].y + heap[i].x]; */
        /* lowIndex[DIMY*heap[i].y + heap[i].x] = lowIndex[DIMY*heap[getParent(i)].y + heap[getParent(i)].x]; */
        /* lowIndex[DIMY*heap[getParent(i)].y + heap[getParent(i)].x] = tmpIndex; */
    }
}

node extractMin(node *heap, long *lastHeapObject)
{
    node min = heap[0];
    if(*lastHeapObject == 0)
    {
        (*lastHeapObject)--;
        return min;
    }
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
    for(int i=0; i <= lastHeapObject; i++)
    {
        printNode(&heap[i]);
    }
}

void fixHeap(node *heap, long i, long lastHeapObject)
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
    n->h = sqrt(pow((DIMX - 1 - n->x),2) + pow((DIMY - 1 - n->y),2));
    /* n->h = 0; */
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
            outNodes[i].prevX = n->x;
            outNodes[i].prevY = n->y;
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
