/* $Id: dp.c,v 1.2 2015/11/08 18:58:21 korpe Exp $ */


#include "dp.h"
#include <stdio.h>

/* 
   - global variable definitions here.
   - define your mutex and condition  variables here (shared) 
   - define your state variables here. (shared)
   - note that the variable you define here are shared threads
   ....
*/


int* forks;
int busy;
int SIZE;

void dp_init(int N)
{
	printf("Hello I am DP library\n");
	if(MINTH <= N && N <= MAXTH){
		forks = (int*)malloc(N * sizeof(int));
		int i;
		for(i = 0; i < N; i++){
			forks[i] = 0;
		}
		busy = 0;
		SIZE = N;
	}
	else{
		printf("Exception in thread \"main\" java.lang.ForkIndexOutOfBoundsException\n");
	}
}

void dp_get_forks(int i)
{
	while(TRUE){
		while(busy){
			sleep(1);
		}
		busy = 1;
		if(forks[i%SIZE] == 0 && forks[i-1%SIZE] == 0){
			forks[i%SIZE] = 1;
			forks[i-1%SIZE] = 1;
			busy = 0;
			break;
		}
		busy = 0;
	}
}

void dp_put_forks(int i)
{
	printf("putting forks\n");
	while(busy){
		sleep(1);
	}
	busy = 1;
	forks[i%SIZE] = 0;
	forks[i-1%SIZE] = 0;
	busy = 0;
}
