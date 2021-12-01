#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "main.h"

#define _GNU_SOURCE

pthread_t tid[PHILOSOPHER_NUM];
pthread_t terminator;
int terminate_flag = 0;
int terminator_id;

int meals_eaten;

void thinking(int sleept) {
	sleep(sleept);
}

int eating(int sleept) {
	sleep(sleept);
	return 1;
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

	pthread_mutex_unlock(&mutex_lock);
}

void* philosopher(void* phil) {
	int *num = (int*)phil;
	int phil_id = *num;
	int sleep_time;
	int loop_count = 0;
	int local_meals = 0;

	while (loop_count < MAX_MEALS && terminate_flag != 1) {
		sleep_time = (int)((random() % (int)MAX_EAT_THINK_SLEEP) + 1);
		thinking(sleep_time);

		if (terminate_flag == 1) {
			break;
		}

		pickup_sticks(phil_id);

		printf("Philsopher %d is eating\n", phil_id);
		sleep_time = (int)((random() % (int)MAX_EAT_THINK_SLEEP) + 1);
		eating(sleep_time);
		meals_eaten++;
		local_meals++;
		if (terminate_flag == 1) {
			return_sticks(phil_id);
			break;
		}

		printf("Philsopher %d is thinking\n", phil_id);
		return_sticks(phil_id);

		loop_count++;
		if (loop_count >= MAX_MEALS) {
			printf("Philosopher %d is full.\n", phil_id);
		}

	}

	if(terminate_flag == 1){
		printf("Philosopher %d is being thrown out :(\n", phil_id);
	}

	printf("Philosopher %d ate: %d meals\n", phil_id, local_meals);
}

void* terminator_t(void* sleept) {
	int* num = (int*)sleept;
	int term_sleep = *num;
	sleep(term_sleep);

	pthread_mutex_lock(&mutex_lock);
	terminate_flag = 1;
	pthread_mutex_unlock(&mutex_lock);
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
		pthread_create(&tid[i], 0, philosopher, (void *)&thread_id[i]);
	}

	pthread_create(&terminator, 0, terminator_t, (void*)&terminator_id);
}

int main(int argc, char* argv[]) {
	int i;
	double sleepy;

	printf("Enter a run time (in seconds): ");
	scanf("%lf", &sleepy);

	terminator_id = sleepy;

	init();
	create_philosopher();

	for (i = 0; i < PHILOSOPHER_NUM; i++) {
		pthread_join(tid[i], NULL);
	}

	printf("Total meals: %d", meals_eaten);
	return 0;
}