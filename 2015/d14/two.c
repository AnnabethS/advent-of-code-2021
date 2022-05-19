#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef TEST
#define DEERAMOUNT 9
#else
#define DEERAMOUNT 2
#endif

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
	deer deers[DEERAMOUNT] = {0};
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

	#ifdef TEST
	deers[0].flySpeed = 14;
	deers[0].flyTime = 10;
	deers[0].restTime = 127;
	deers[1].flySpeed = 16;
	deers[1].flyTime = 11;
	deers[1].restTime = 162;
	#endif

	uint points[DEERAMOUNT] = {0};
	char win[DEERAMOUNT] = {0};
	#ifdef TEST
	#define STEPS 1000
	#else
	#define STEPS 2503
	#endif

	for(int i=0; i <= STEPS; i++)
	{
		memset(win, 0, sizeof(char)*DEERAMOUNT);
		deer* furthestDeer = &deers[0];
		win[0] = 1;
		for(int j=0; j < DEERAMOUNT; j++)
		{
			updateDeer(&deers[j]);
			if(deers[j].distance > furthestDeer->distance)
			{
				memset(win, 0, sizeof(char)*DEERAMOUNT);
				win[j] = 1;
				furthestDeer = &deers[j];
			}
			else if(deers[j].distance == furthestDeer->distance)
			{
				win[j] = 1;
			}
		}
		for(int j=0; j < DEERAMOUNT; j++)
		{
			points[j] += win[j];
		}
	}
	int maxPoints = 0;
	for(int i=0; i < DEERAMOUNT; i++)
	{
		if (points[i] > maxPoints)
			maxPoints = points[i];
	}
	printf("points: %d\n", maxPoints);
}

void updateDeer(deer* d)
{
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
	if(!d->isResting)
		d->distance += d->flySpeed;
	d->currentTime++;
}
