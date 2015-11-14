/* $Id: hash.c,v 1.2 2015/11/08 18:47:10 korpe Exp $ */


#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "hash.h"

#define lock pthread_mutex_lock
#define unlock pthread_mutex_unlock

/* 
   hash table definition here - array of linked lists. 
   it is a shared data structure 
*/

pthread_mutex_t writemut = PTHREAD_MUTEX_INITIALIZER;
struct node ** list;
int SIZE;

void hash_init(int N)
{
	printf("hash init\n");
	if(N >= 10 && N <= 100){
		list = (struct node**)malloc(N * sizeof(struct node*));
		SIZE = N;
	}
	else{
		printf("N value is invalid\n");
	}
	
}

int hash_insert(int k)
{
	printf("hash inserting %d\n", k);

    struct node * ptr = list[k%SIZE];
    lock(&writemut);
    while(ptr != NULL){
    	if(ptr -> data == k){
    		return -1;
    	}
    	ptr = ptr->next;
    }
    ptr = (struct node*)malloc(sizeof(struct node *));
    ptr->data = k;
    unlock(&writemut);

	return (0);
}

int hash_delete(int k)
{
    printf("hash deleting %d\n", k);
    struct node * ptr = list[k%SIZE];
    lock(&writemut);
    if(ptr != NULL){
    	if(ptr -> data == k){
    		list[k%SIZE] = ptr -> next;
    		free(ptr);
    		unlock(&writemut);
    		return 0;
    	}
    }
    int found = 0;
    while(!found && ptr->next != NULL){
    	if(ptr -> next -> data == k){
    		found = 1;
    		struct node* temp = ptr -> next;
    		ptr->next = ptr->next->next;
    		free(temp);
    		unlock(&writemut);
    		return 0;
    	}
    }
    unlock(&writemut);

	return -1;
}

int hash_get(int k)
{
	lock(&writemut);
	struct node* ptr = list[k%SIZE];
	while(ptr != NULL){
		if(ptr -> data == k){
			return k;
		}
	}
	unlock(&writemut);

	return -1;
}
