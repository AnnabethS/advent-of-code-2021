#include <stdio.h>
#include <stdlib.h>

#define DEERAMOUNT 9


typedef struct deer{
	int flySpeed; //speed that the reindeer can fly at
	int flyTime; //time the reindeer can fly for
	int restTime; //time the reindeer must rest for
	char isResting; //1 if the reindeer is currently resting
	int currentTime; //current time spent in the stage
	int distance; //current distance covered
}deer;

void updateDeer(deer* d);

FILE* fp;

int main()
{
	deer deers[DEERAMOUNT];
	fp = fopen("input.txt", "r");
	char flySpeed[10] = {0};
	char flyTime[10] = {0};
	char restTime[10] = {0};
	for(int i=0; i < DEERAMOUNT; i++)
	{
		fscanf(fp, "%s can fly %s km/s for %s seconds,"
						" but then must rest for %s seconds.\n",
						flySpeed, flySpeed, flyTime, restTime);
		deers[i].flySpeed = strtol(flySpeed, NULL, 10);
		deers[i].flyTime = strtol(flyTime, NULL, 10);
		deers[i].restTime = strtol(restTime, NULL, 10);
		deers[i].isResting = 0;
		deers[i].currentTime = 0;
		deers[i].distance = 0;
	}	

	deer test;
	test.currentTime = 0;
	test.isResting = 0;
	test.restTime = 127;
	test.flyTime = 10;
	test.flySpeed = 14;
	test.distance = 0;
	for(int i=0; i < 1000; i++)
	{
		updateDeer(&test);
		printf("%d -> %d\n", i+1, test.distance);
	}

	for(int i=0; i <= 2503; i++)
	{
		for(int j=0; j < DEERAMOUNT; j++)
			updateDeer(&deers[j]);
	}
	int best = 0;
	for(int i=0; i < DEERAMOUNT; i++)
	{
		if(deers[i].distance > best)
			best = deers[i].distance;
	}
	printf("highest_distance: %d\n", best);
}

void updateDeer(deer* d)
{
	if(!d->isResting)
		d->distance += d->flySpeed;
	d->currentTime++;
	if(d->isResting)
	{
		if(d->currentTime >= d->restTime)
		{
			d->currentTime = 0;
			d->isResting = 0;
		}
	}
	else
	{
		if(d->currentTime >= d->flyTime)
		{
			d->currentTime = 0;
			d->isResting = 1;
		}
	}
}
