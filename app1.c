
/* $Id: app1.c,v 1.1 2015/11/08 18:25:06 korpe Exp $ */

#include <pthread.h>
#include "dp.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void *philosopher(void *p)
{
	int num = (long)p;

	/* think - in THINKING stte */
	sleep(1);
	dp_get_forks(num);
	/* eat – in EATING state */
	sleep(1);
	dp_put_forks(num);
	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	pthread_t tid[MAXTH];
	int N = atoi(argv[1]);
	int i;
	printf("initialize dp lib\n");
	dp_init(N);

	for (i = 0; i < N; ++i) {
		pthread_create(&tid[i], NULL, &philosopher, (void *)(long)i);
	}

	for (i = 0; i < N; ++i)
		pthread_join(tid[i], NULL);

	return (0);
}
