/* $Id: dp.h,v 1.1 2015/11/08 18:26:48 korpe Exp $ */

#ifndef DP_H
#define DP_H

#define MAXTH 20
#define MINTH 5

void dp_init(int N);
void dp_get_forks(int i);
void dp_put_forks(int i);

#endif				/* DP_H */
