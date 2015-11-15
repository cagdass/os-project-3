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

pthread_mutex_t *muts;
struct node ** list;
int SIZE;

// void printlist(struct node* ptr){
// 	while(ptr != NULL){
// 		printf("%d -> ", ptr->data);
// 		ptr = ptr->next;
// 	}
// }

void hash_init(int N)
{
	printf("hash init\n");
	if(N <= MAXTH){
		srand( time(NULL));
		// SIZE = 10 + (rand() % 90);
		SIZE = 10;
		printf("Number of buckets is %d\n", SIZE);
		list = (struct node**)malloc(SIZE * sizeof(struct node*));
		muts = (pthread_mutex_t *)malloc(SIZE * sizeof(pthread_mutex_t));
		int i;
		for(i = 0; i < SIZE; i++){
			pthread_mutex_init(&muts[i], NULL);
		}
	}
	else{
		printf("N value is invalid\n");
	}
	
}

int hash_insert(int k)
{
    lock(&muts[k%SIZE]);
    int index = k%SIZE;
    printf("hash inserting %d in bucket %d\n", k, index);
    struct node * ptr = list[index];
    if(ptr == NULL){
    	list[index] = (struct node*)malloc(sizeof(struct node));
    	list[index] -> data = k;
        list[index] -> next = NULL;
    	unlock(&muts[index]);
    	return 0;
    }
    else{
    	while(ptr -> next != NULL){
	    	printf("%d -> in bucket %d\n", ptr->data, index);
	    	if(ptr -> data == k){
	    		printf("zaten var %d\n", k);
	    		unlock(&muts[index]);
	    		return -1;
	    	}
	    	ptr = ptr->next;
	    }
	    if(ptr -> data == k){
	    	printf("zaten var ki %d\n", k);
    		unlock(&muts[index]);
    		return -1;
	    }
	    ptr->next = (struct node*)malloc(sizeof(struct node));
	    ptr->next->data = k;
        ptr->next->next = NULL;
	    unlock(&muts[index]);
	    return (0);
    }
    
    // printf("after inserting %d in bucket %d, bucket is like\n", k, k%SIZE);
    // printlist(list[k%SIZE]);
    
}

int hash_delete(int k)
{
    lock(&muts[k%SIZE]);
    int index = k%SIZE;
    printf("hash deleting %d from bucket %d\n", k, index);
    struct node * ptr = list[index];
    if(ptr != NULL){
    	if(ptr -> data == k){
    		printf("deleting from %d -> in bucket %d\n", ptr->data, index);
    		list[index] = ptr -> next;
    		free(ptr);
    		printf("Das root is %d\n", k);
    		// printf("%d -> ", ptr->data);
    		printf("after deleting %d from bucket %d, bucket is like\n", k, index);
    		// printlist(list[k%SIZE]);
    		unlock(&muts[index]);
    		return 0;
    	}
    }
    else{
    	printf("root is null for %d\n", k);
    	unlock(&muts[index]);
    	return -1;
    }

    while(ptr->next != NULL){
    	printf("Delete %d - %d -d> bucket: %d\n", k, ptr->data, index);
    	if(ptr -> next -> data == k){
    		struct node* temp = ptr -> next;
    		ptr->next = ptr->next->next;
    		free(temp);
    		printf("after deleting %d from bucket %d, bucket is like\n", k, index);
    		// printlist(list[k%SIZE]);
    		unlock(&muts[index]);
    		return 0;
    	}
    	printf("Allah\n");
    	ptr = ptr->next;
    }
    printf("Can't delete %d\n", k);
    unlock(&muts[index]);
    
	return -1;
}

int hash_get(int k)
{
	lock(&muts[k%SIZE]);
	int index = k%SIZE;
	printf("get value %d in bucket %d\n", k, index);
	struct node* ptr = list[index];
	while(ptr != NULL){
		if(ptr -> data == k){
			unlock(&muts[index]);
			return k;
		}
	}
	printf("got it the value %d in bucket %d\n", k, index);
	unlock(&muts[index]);

	return -1;
}
