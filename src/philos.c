#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include "dp.h"
 
void *philosopher(void *param)
{
    int *lnumber = (int *)param;
    int number = *lnumber;
    int sleepTime;
    int loopCount = 0;
 
    srandom((unsigned)time(NULL));
 
    while (loopCount < 5) {
        sleepTime = (int)((random() % MAX_SLEEP_TIME) + 1);
        thinking(sleepTime);
 
        pickup_forks(number);
 
        printf("Philosopher %d is eating\n",number);
 
        sleepTime = (int)((random() % MAX_SLEEP_TIME) + 1);
        eating(sleepTime);
 
        printf("Philosopher %d is thinking\n",number);
        return_forks(number);
         
        loopCount++;
    }
}