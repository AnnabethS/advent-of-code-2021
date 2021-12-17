#include <stdlib.h>
#include <stdio.h>

#ifdef TEST
#define TARGETX 20
#define TARGETY -10
#define TARGETX2 30
#define TARGETY2 -5
#else
#define TARGETX 265
#define TARGETY -103
#define TARGETX2 287
#define TARGETY2 -58
#endif

char isHit(int xVel, int yVel);

int main()
{
    char hit = 0;
    int count = 0;
    for(int i=0; i < 1000; i++)
    {
        for(int j=-1000; j < 1000; j++)
        {
            if(isHit(i, j) == 1)
                count++;
        }
    }
    printf("distinct values: %d\n", count);
}

// returns 0 on a too close miss
// returns 1 on a hit
// returns 2 on a too far miss
char isHit(int xVel, int yVel)
{
    char hit = 0;
    int x = 0;
    int y = 0;
    char stepBeforeTarget = 0;
    while(1)
    {
        x += xVel;
        y += yVel;

        xVel--;
        if(xVel < 0)
            xVel = 0;
        yVel--;


        if(x < TARGETX)
            stepBeforeTarget = 1;

        if(x >= TARGETX && x <= TARGETX2 &&
           y >= TARGETY && y <= TARGETY2)
        {
            hit = 1;
            break;
        }
        if(y < TARGETY)
        {
            // we have missed the target zone
            hit = 0;
            break;
        }
        if(x > TARGETX2)
        {
            if(stepBeforeTarget)
                hit = 0;
            else
                hit = 2;
            break;
        }
    }
    return hit;
}
