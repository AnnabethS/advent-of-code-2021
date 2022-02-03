#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef DEBUG
#define FILENAME "test.txt"
#define BUFLENGTH 11
#else
#define FILENAME "input.txt"
#define BUFLENGTH 1000
#endif

typedef struct fish{
	int timer;
	struct fish* next;
}fish;

int main()
{
	FILE* fp;
	fp = fopen(FILENAME, "r");

	char buf[BUFLENGTH];
	fscanf(fp, "%s", buf);
	fclose(fp);

	fish* head = malloc(sizeof(fish));


	fish* tail = head;

	char* nextNum = strtok(buf, ",");
	head->timer = strtol(nextNum, NULL, 10);
	
	nextNum = strtok(NULL, ",");

	while(nextNum != NULL)
	{
		tail->next = malloc(sizeof(fish));
		tail = tail->next;
		tail->timer = strtol(nextNum, NULL, 10);
		nextNum = strtok(NULL, ",");
	}


	tail->next = NULL;

	fish* curr = head;
	/* while(curr != NULL) */
	/* { */
	/* 	printf("%d ", curr->timer); */
	/* 	curr = curr->next; */
	/* } */
	/* printf("\n"); */

	const int days = 80;
	int newFish = 0;
	/* fish* newfish_head = NULL; */
	/* fish* newfish_tail = NULL; */

	for(int i=0; i < days; i++)
	{
		curr = head;
		newFish = 0;
		while(curr != NULL)
		{
			if(curr->timer==0)
			{
				curr->timer = 6;
				newFish++;
			}
			else
			{
				curr->timer--;
			}
			curr = curr->next;
		}
		for(int j=0; j < newFish; j++)
		{
			tail->next = malloc(sizeof(fish));
			tail = tail->next;
			tail->timer = 8;
			tail->next = NULL;
		}
		curr = head;
		/* while(curr != NULL) */
		/* { */
		/* 	printf("%d ", curr->timer); */
		/* 	curr = curr->next; */
		/* } */
		/* printf("\n"); */
	}

	curr = head;
	int numFish = 0;
	while(curr!=NULL)
	{
		numFish++;
		curr = curr->next;
	}
	printf("fish: %d\n", numFish);

	/* curr = head; */
	/* while(curr->next != NULL) */
	/* { */
	/* 	printf("%d ", curr->timer); */
	/* 	curr = curr->next; */
	/* } */
	/* printf("\n"); */
}
