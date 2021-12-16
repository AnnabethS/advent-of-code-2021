#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef TEST
#define FILENAME "test.txt"
#define DIMX 10
#define DIMY 10
#else
#define FILENAME "input.txt"
#define DIMX 100
#define DIMY 100
#endif

typedef struct node{
    int x;
    int y;
    int g;
    int h;
    int f;
    // previous node IN THE PATH
    struct node *prev;
    // next node IN THE LINKED LIST
    struct node *next;
}node;

char addToQueue(node *n, node **head);
void getCosts(node *n, int cost[DIMY][DIMX]);
void printNode(node *n);
void getSuccessors(node *n, node *outNodes[4], int cost[DIMY][DIMX]);
node* popFromQueue(node **head);
int getNodeFFromQueue(node* n, node *head);

int main()
{
    FILE* fp = fopen(FILENAME, "r");
    int cost[DIMY][DIMX];

    for(int y=0; y < DIMY; y++)
    {
        for(int x=0; x < DIMX; x++)
        {
            char bufChar;
            fscanf(fp, "%c", &bufChar);
            cost[y][x] = bufChar - '0';
        }
        char buf2;
        fscanf(fp, "%c", &buf2);
    }

    fclose(fp);

    // both queues are priority queues sorted by node.f with low f being higher priority
    
    // item 1 of the open queue
    node* openQHead = (node*) malloc(sizeof(node));
    /* openQHead->x = openQHead->y = openQHead->f = openQHead->g =  */
    /* openQHead->prev = NULL; // opening node */
    /* openQHead->next = NULL; */

    memset(openQHead, 0, sizeof(node));

    printNode(openQHead);

    // item 1 of the closed queue
    /* node* closedListHead = (node*) malloc(sizeof(node)); */

    node* closedListHead = NULL;

    char goalFound = 0;

    node* goal = NULL;
    
    while(openQHead !=NULL)
    {
        node *succ[4] = {NULL};
        node *currNode = popFromQueue(&openQHead);
        /* printNode(currNode); */
        getSuccessors(currNode, succ, cost);
        for (int i=0; i < 4; i++)
        {
            /* node *ptr = openQHead; */
            /* printf("open list: \n"); */
            /* printf("c: ");printNode(currNode); */
            /* while(ptr != NULL) */
            /* { */
            /*     printNode(ptr); */
            /*     ptr = ptr->next; */
            /* } */

            /* printf("closed list: \n"); */
            /* ptr = closedListHead; */
            /* while (ptr != NULL) */
            /* { */
            /*     printNode(ptr); */
            /*     ptr = ptr->next; */
            /* } */
            /* printf("\n\n"); */

            /* printf("start loop\n"); */
            if(succ[i] == NULL)
            {
                /* printf("unviable successor\n"); */
                free(succ[i]);
                continue;
            }
            if(succ[i]->x == DIMX-1 && succ[i]->y == DIMY-1)
            {
                /* printf("goal successor\n"); */
                // this successor is the goal, we can stop now
                goal = succ[i];
                goalFound = 1;
                break;
            }
            int closedValue = getNodeFFromQueue(succ[i], closedListHead);
            if(closedValue != -1 && closedValue <= succ[i]->f)
            {
                /* printf("successor in goal list\n"); */
                free(succ[i]);
                continue;
            }
            addToQueue(succ[i], &openQHead);
        }
        currNode->next = NULL;
        addToQueue(currNode, &closedListHead);
        /* popFromQueue(&openQHead); */
        if(goalFound)
            break;
    }

    /* char visited[DIMY][DIMX] = {0}; */
    int total = 0;
    while(goal->prev != NULL)
    {
        /* printNode(goal); */
        total += cost[goal->y][goal->x];
        /* visited[goal->y][goal->x] = 1; */
        goal = goal->prev;
    }
    /* visited[0][0] = 1; */
    /* for(int i=0; i < DIMY; i++) */
    /* { */
    /*     for(int j=0; j < DIMX; j++) */
    /*     { */
    /*         if(visited[i][j]) */
    /*             printf("%d", cost[i][j]); */
    /*         else */
    /*             printf(" "); */
    /*     } */
    /*     printf("\n"); */
    /* } */
    /* for(int i=0; i < DIMY; i++) */
    /* { */
    /*     for(int j=0; j < DIMX; j++) */
    /*     { */
    /*         printf("%d", cost[i][j]); */
    /*     } */
    /*     printf("\n"); */
    /* } */

    printf("goal: %d", total);
}

//returns 0 if the node was not added, 1 otherwise
char addToQueue(node *n, node **head)
{
    //catch the case where the list is empty
    /* printf("\n\nnew addtoqueue\n"); */
    /* printNode(n); */
    if(*head == NULL)
    {
        /* printf("head is NULL\n"); */
        *head = n;
        return 1;
    }
    
    //catch the case where n.f < head.f
    if(n->f < (*head)->f)
    {
        /* printf("inserting at pos 0\n"); */
        /* printf("n: "); */
        /* printNode(n); */
        /* printf("head: "); */
        /* printNode(*head); */
        node* oldHead = *head;
        *head = n;
        n->next = oldHead;
        return 1;
    }
    
    node *ptr = *head;
    node *prev_ptr = NULL;
    while(ptr != NULL)
    {
        /* printf("checking ll\n"); */
        if(ptr->x == n->x && ptr->y == n->y)
        { //this node is already in the list, with a lower path cost
           /* printf("node already in list, exiting\n"); */
            return 0;
        }
        /* printf("n: ");printNode(n); */
        /* printf("ptr: ");printNode(ptr); */
        if(ptr->f > n->f)
        {
            /* printf("inserting node in middle of list\n"); */
            prev_ptr->next = n;
            n->next = ptr;
            return 1;
        }
        prev_ptr = ptr;
        ptr = ptr->next;
        /* if(ptr != NULL) */
        /*     printNode(ptr); */
        
    }
    /* printf("inserting node at end of list\n"); */
    prev_ptr->next = n;
    return 1;
}

node* popFromQueue(node **head)
{
    node *oldHead = *head;
    *head = (*head)->next;
    return oldHead;
}

int getNodeFFromQueue(node* n, node *head)
{
    node *ptr = head;
    while(ptr != NULL)
    {
        if(ptr->x == n->x && ptr->y == n->y)
            return ptr->f;
        ptr = ptr->next;
    }
    return -1;
}

void getCosts(node *n, int cost[DIMY][DIMX])
{
    if(n->prev != NULL)
        n->g = cost[n->y][n->x] + n->prev->g;
    else
        n->g = 0;
    /* n->h = (DIMX - 1 - n->x) + (DIMY - 1 - n->y); */
    n->h = 0;
    n->f = n->g + n->h;
}

void getSuccessors(node *n, node *outNodes[4], int cost[DIMY][DIMX])
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
            outNodes[i] = (node*) malloc(sizeof(node));
            outNodes[i]->x = x;
            outNodes[i]->y = y;
            outNodes[i]->prev = n;
            outNodes[i]->next = NULL;
            getCosts(outNodes[i], cost);
        }
        else
        {
            outNodes[i] = NULL;
        }
    }
}

void printNode(node *n)
{
    printf("x: %d, y: %d, f: %d\n", n->x, n->y, n->f);
}
