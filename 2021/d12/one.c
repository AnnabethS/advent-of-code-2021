#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef TEST
#define LINES 10
#define FILENAME "test.txt"
#else
#define LINES 23
#define FILENAME "input.txt"
#endif

typedef struct connection{
	char a[3];
	char b[3];
}connection;

typedef struct node{
        char path[(LINES*3)+1];
	char pathHead[3];
	struct node* next;
}node;

void printConnection(connection *c);

void getPathHead(node* n);

char isInPath(const char *path, const char *node);

int main()
{
	FILE* fp = fopen(FILENAME, "r");
	connection cons[LINES];
	char bufStr[9];
	for(int i=0; i<LINES; i++)
	{
		fscanf(fp, "%s", bufStr);
		char tmpstr[9];
		strcpy(tmpstr, strtok(bufStr, "-"));
		if(strcmp(tmpstr, "start") == 0)
			strcpy(cons[i].a, "<<\0");
		else if(strcmp(tmpstr, "end") == 0)
			strcpy(cons[i].a, ">>\0");
		else
			strcpy(cons[i].a, tmpstr);

		strcpy(tmpstr, strtok(NULL, "-"));
		if(strcmp(tmpstr, "start") == 0)
			strcpy(cons[i].b, "<<\0");
		else if(strcmp(tmpstr, "end") == 0)
			strcpy(cons[i].b, ">>\0");
		else
			strcpy(cons[i].b, tmpstr);

		printConnection(&cons[i]);
	}
	
	//points to the first item in the open (working) list
	node* openListHead = malloc(sizeof(node));
	//points to the last item in the open (working) list
	node* openListTail = openListHead;

	//points to the first item in the closed (finished path) list
	node* closedListHead = malloc(sizeof(node));
	//points to the last item in the closed (finished path) list
	node* closedListTail = closedListHead;

	strcpy(openListHead->path, "<<,\0");
	getPathHead(openListHead);

	while(openListHead != NULL)
	{
		for(int i=0; i < LINES; i++)
		{
			char *newNode = NULL;
			if(strcmp(openListHead->pathHead, cons[i].a) == 0)
				newNode = &cons[i].b[0];
			else if (strcmp(openListHead->pathHead, cons[i].b) == 0)
				newNode = &cons[i].a[0];


			/* printf("node %s | path %s | head %s\n", newNode, openListHead->path, */
					/* openListHead->pathHead); */

			if(newNode == NULL)
				continue; //this connection doesnt involve the path head

			if(strcmp(newNode, "<<") == 0)
				continue; //dont go back to the start

			/* if(strcmp(newNode, ">>") == 0) */
			/* { */
			/* 	printf("tried to eval an ended string\n"); */
			/* 	continue; */
			/* } */

			/* printf("****************\n current path: %s\n", openListHead->path); */

			/* printf("connection used: %s <-> %s\n", */
			/* 		openListHead->pathHead, newNode); */

			if(newNode[0] >= 'A' && newNode[0] <= 'Z')
			{ //capital
				/* printf("head (upper) %s\n", newNode); */
			}
			else if (newNode[0] >= 'a' && newNode[0] <= 'z')
			{ //lowercase
				/* printf("head (lower) %s\n", newNode); */
				if(isInPath(openListHead->path, newNode))
					continue;
			}
			else if (strcmp(newNode, ">>\0") == 0)
			{ //we are pathing to the end
				closedListTail->next = malloc(sizeof(node));
				closedListTail = closedListTail->next;
				closedListTail->next = NULL;
				char newPath[(LINES*3)+1];
				strcpy(newPath, openListHead->path);
				strcat(newPath, newNode);
				strcat(newPath, ",\0");
				strcpy(closedListTail->path, newPath);
				printf("ENDPATH: %s\n", closedListTail->path);
				continue; // dont add this one to the open list
			}
			else
			{ //error
				printf("Error passing pathHead (%s), exiting\n",
						openListHead->pathHead);
				openListHead = NULL;
				break;
			}

			openListTail->next = malloc(sizeof(node));
			openListTail = openListTail->next;
			openListTail->next = NULL;
			char newPath[(LINES*3)+1];
			strcpy(newPath, openListHead->path);
			strcat(newPath, newNode);
			strcat(newPath, ",\0");
			strcpy(openListTail->path, newPath);
			/* printf("new path: %s\n", newPath); */
			getPathHead(openListTail);
		}
		node *node_print_ptr = openListHead;
		/* printf("******* open list state *********\n"); */
		while(node_print_ptr != NULL)
		{
			/* printf("%s\n", node_print_ptr->path); */
			node_print_ptr = node_print_ptr->next;
		}
		if(openListHead != NULL)
		{
			if(openListHead->next == NULL)
				break;
			/* printf("rm: %s\n", openListHead->path); */
			node *next = openListHead->next;
			free(openListHead);
			openListHead = next;
		}
	}

	/* printf("closed lists\n"); */
	node *next = closedListHead;
	int count = -1;
	while(next != NULL)
	{
		count++;
		/* printf("%s\n", next->path); */
		next = next->next;
	}
	printf("total paths: %d\n", count);

}

char isInPath(const char *path, const char *node)
{
	char tmpPath[(LINES*3)+1];
	strcpy(tmpPath, path);

	char *section = strtok(tmpPath, ",");
	while(section != NULL)
	{
		if(strcmp(section, node) == 0)
			return 1;
		section = strtok(NULL, ",");
	}
	return 0;
}

void getPathHead(node *n)
{
	char tmpPath[(LINES*3)+1];
	strcpy(tmpPath, n->path);
	char *tmp;
	char *prev;
	tmp = strtok(tmpPath, ",");
	while(tmp!=NULL)
	{
		prev = tmp;
		tmp = strtok(NULL, ",");
	}
	strcpy(n->pathHead, prev);
}

void printConnection(connection *c)
{
	printf("%s <-> %s\n", c->a, c->b);
}
