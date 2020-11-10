#ifndef _GEN_H_
#define _GEN_H_

#define min2(X,Y) X<Y?X:Y
#define min3(X,Y,Z) X<Z ? (X<Y?X:Y) : (Z<Y?Z:Y)
#define max2(X,Y) X>Y?X:Y
#define max3(X,Y,Z) X>Z ? (X>Y?X:Y) : (Z>Y?Z:Y)

void swap(int *x, int *y);

#endif
