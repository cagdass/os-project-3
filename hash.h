/* $Id: hash.h,v 1.1 2015/11/08 18:26:48 korpe Exp $ */


#ifndef HASH_H
#define HASH_H

#define MAXTH 20

#define MINBUCKETS 10
#define MAXBUCKETS 100

void hash_init(int N);

int hash_insert(int k);

int hash_delete(int k);

int hash_get(int k);

#endif				/* HASH_H */
