#ifndef _INTGEN_H_
#define _INTGEN_H_

#include <limits.h>
#include <inttypes.h>

#define LOWER_BOUND 0
#define UPPER_BOUND INT_MAX

int gen_int(int lb, int ub);
int* gen_ints(int size, int lb, int ub, double inversions);

#endif
