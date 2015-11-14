/* $Id: dp.c,v 1.2 2015/11/08 18:58:21 korpe Exp $ */


#include "dp.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

/* 
   - global variable definitions here.
   - define your mutex and condition  variables here (shared) 
   - define your state variables here. (shared)
   - note that the variable you define here are shared threads
   ....
*/

#define lock pthread_mutex_lock
#define unlock pthread_mutex_unlock


int* forks;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
int SIZE = 0;

void dp_init(int N)
{
	printf("Hello I am DP library\n");
	if(MINTH <= N && N <= MAXTH){
		forks = (int*)malloc(N * sizeof(int));
		int i;
		for(i = 0; i < N; i++){
			forks[i] = 0;
		}
		SIZE = N;
	}
	else{
		printf("Exception in thread \"main\" java.lang.ForkIndexOutOfBoundsException\n");
	}
}

void dp_get_forks(int i)
{
	if(SIZE >= 5 && SIZE <= 20){
		int right = i;
    	int left = (i - 1 == -1) ? SIZE - 1 : (i - 1);
		while(1){
            lock(&mut);
            if(forks[right] || forks[left])
            {
                unlock(&mut);     // give up the forks unless you can take both at once.
                printf("Philosopher %d cannot take forks. Giving up and thinking.\n",i); 
                sleep(1);
                continue;
            }
            if(i % 2 == 0){
            	forks[right] = 1; // take right fork first.
            	printf("Philosopher %d took fork %d\n", i, right);
            	forks[left] = 1;
            	printf("Philosopher %d took fork %d\n", i, left);
            	unlock(&mut);
            	break;
            }
            else{
            	forks[left] = 1; // take left fork first.
            	printf("Philosopher %d took fork %d\n", i, left);
            	forks[right] = 1;
            	printf("Philosopher %d took fork %d\n", i, right);
            	unlock(&mut);
            	break;
            }
            
            
            
        }
	}
	else{
		printf("Forgot to initialize?\n");
	}
	
}

void dp_put_forks(int i)
{
	if(SIZE >= 5 && SIZE <= 20){
		int right = i;
    	int left = (i - 1 == -1) ? SIZE - 1 : (i - 1);
        forks[right] = 0;
        printf("Philosopher %d gave up fork %d\n", i, right);
        forks[left] = 0;
        printf("Philosopher %d gave up fork %d\n", i, left);
	}
	else{
		printf("Forgot to initialize?\n");
	}
}
