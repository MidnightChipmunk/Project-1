/**Header file for dining philosophers*/
 
#include <pthread.h>
#define NUMBER      5
#define MAX_SLEEP_TIME  5

enum {THINKING, HUNGRY, EATING} state[NUMBER];
int thread_id[NUMBER];

pthread_cond_t      cond_vars[NUMBER];
pthread_mutex_t     mutex_lock;

void *philosopher(void *param);