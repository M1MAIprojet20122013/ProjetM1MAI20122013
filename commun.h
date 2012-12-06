#ifndef COMMUN_H
#define COMMUN_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <math.h>

#define square(x) (x)*(x)

typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned char uint8;

double integrate(double a, double b, double (*f)(double x)); // f est une fonction de callback http://en.wikipedia.org/wiki/Callback_%28computer_programming%29

#ifdef __cplusplus
}
#endif

#endif
