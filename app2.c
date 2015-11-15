/* $Id: app2.c,v 1.2 2015/11/08 18:47:10 korpe Exp $ */


#include <pthread.h>
#include "hash.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void *worker(void *p)
{
	int i;
        int num = (long) p; 

	for (i = 0; i < 5; ++i) {
		hash_insert(num*10 + i);
	}

	for (i = 20; i < 25; ++i) {
		hash_delete(num*10 + i);
	}

	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	clock_t start, end;
	start = clock();
	
	pthread_t tid[MAXTH];
	int i;
	int N;

	N = atoi(argv[1]);

	if (N > MAXTH) {
		printf("Can create  at most %d threads\n", MAXTH);
		exit(1);
	}

	hash_init(N);

	for (i = 0; i < N; ++i) {
		pthread_create(&tid[i], NULL, &worker, (void *)(long)i);
	}

	for (i = 0; i < N; ++i)
		pthread_join(tid[i], NULL);

	end = clock();
    printf( "Number of seconds: %f\n", (end-start)/(double)CLOCKS_PER_SEC );

	return (0);
}
