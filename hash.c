/* $Id: hash.c,v 1.2 2015/11/08 18:47:10 korpe Exp $ */


#include <stdlib.h>
#include <stdio.h>
#include "hash.h"

/* 
   hash table definition here - array of linked lists. 
   it is a shared data structure 
*/

void hash_init(int N)
{
	printf("hash init\n");
}

int hash_insert(int k)
{
        printf("hash inserting %d\n", k);

	return (0);
}

int hash_delete(int k)
{
        printf("hash deleting %d\n", k);

	return (0);
}

int hash_get(int k)
{
        printf("hash getting %d\n", k);

	return (0);
}
