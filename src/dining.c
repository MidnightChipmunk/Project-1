
#include <pthread.h>
#include <stdio.h>
#include "dp.h"

int leftNeighbor(int number)
{
    if (number == 0)
        return NUMBER - 1;
    else
        return number - 1;
}

int rightNeighbor(int number)
{
    if (number == NUMBER - 1)
        return 0;
    else
        return number + 1;
}
 
void checkNeighbor(int i)
{
    if ( (state[leftNeighbor(i)] != EATING) && (state[i] == HUNGRY) && (state[rightNeighbor(i)] != EATING) ) {
        state[i] = EATING;
        pthread_cond_signal(&cond_vars[i]);
    }
}
 
void pickup_forks(int number)
{
    pthread_mutex_lock(&mutex_lock);
 
    state[number] = HUNGRY;
    checkNeighbor(number);
 
    while (state[number] != EATING) {
        pthread_cond_wait(&cond_vars[number], &mutex_lock);
    }
 
    pthread_mutex_unlock(&mutex_lock);
}

void return_forks(int number)
{
    pthread_mutex_lock(&mutex_lock);
 
    state[number] = THINKING;
    checkNeighbor(leftNeighbor(number));
    checkNeighbor(rightNeighbor(number));
 
    pthread_mutex_unlock(&mutex_lock);
}