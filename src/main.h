#include <pthread.h>

#define PHILOSOPHER_NUM 5
#define MAX_MEALS 10

enum{THINKING, HUNGRY, EATING} state[PHILOSOPHER_NUM];
int thread_id[PHILOSOPHER_NUM];

pthread_cond_t phil_cond[PHILOSOPHER_NUM];
pthread_mutex_t mutex_lock;

