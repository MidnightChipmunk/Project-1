#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "main.h"

#define _GNU_SOURCE

pthread_t tid[PHILOSOPHER_NUM];
int meals_eaten;
double MAX_EAT_THINK_SLEEP = 10;

void thinking(int sleept) {
	sleep(sleept);
}

void eating(int sleept) {
	sleep(sleept);
}

int get_left(int phil) {
	if (phil == 0) {
		return PHILOSOPHER_NUM - 1;
	}
	else{
		return phil - 1;
	}
}

int get_right(int phil) {
	if (phil == PHILOSOPHER_NUM - 1) {
		return 0;
	}
	else {
		return phil + 1;
	}

}

void can_eat(int phil) {
	if ((state[get_left(phil)] != EATING) && (state[phil] == HUNGRY) && (state[get_right(phil)] != EATING)) {
		state[phil] = EATING;
		pthread_cond_signal(&phil_cond[phil]);
	}
}

void pickup_sticks(int phil) {
	pthread_mutex_lock(&mutex_lock);

	state[phil] = HUNGRY;
	can_eat(phil);

	while (state[phil] != EATING) {
		pthread_cond_wait(&phil_cond[phil], &mutex_lock);
	}

	pthread_mutex_unlock(&mutex_lock);
}

void return_sticks(int phil) {
	pthread_mutex_lock(&mutex_lock);

	state[phil] = THINKING;
	can_eat(get_left(phil));
	can_eat(get_right(phil));
}

void* philosopher(void* phil) {
	int *num = (int*)phil;
	int phil_id = *num;
	int sleep_time;
	int loop_count = 0;
	int meals_eaten = 0;

	while (loop_count < 5) {
		sleep_time = (int)((rand() % (int)MAX_EAT_THINK_SLEEP) + 1);
		thinking(sleep_time);

		pickup_sticks(phil_id);

		printf("Philsopher %d is eating\n", phil_id);
		sleep_time = (int)((rand() % (int)MAX_EAT_THINK_SLEEP) + 1);
		eating(sleep_time);
		meals_eaten++;

		printf("Philsopher %d is thinking\n", phil_id);
		return_sticks(phil_id);

		loop_count++;

		if (meals_eaten >= MAX_MEALS)
			break;
	}
}

void init(){
	int i;
	for (i = 0; i < PHILOSOPHER_NUM; i++) {
		state[i] = THINKING;
		thread_id[i] = i;
		pthread_cond_init(&phil_cond[i], NULL);
	}

	pthread_mutex_init(&mutex_lock, NULL);
}

void create_philosopher()
{
	int i;
	for (i = 0; i < PHILOSOPHER_NUM; i++) {
		pthread_create(tid[i], 0, philosopher, (void*)thread_id[i]);
	}
}

int main(int argc, char* argv[]) {
	int i;
	MAX_EAT_THINK_SLEEP = strtod(argv[1]);

	init();
	create_philosopher();

	sleep(argv[2]);
	for (i = 0; i < PHILOSOPHER_NUM; i++) {
		pthread_join(tid[i], NULL);
	}

	sleep();
	return 0;
}