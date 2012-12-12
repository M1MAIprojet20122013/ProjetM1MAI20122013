#ifndef PLOT_H
#define PLOT_H

#ifdef __cplusplus
extern "C"
{
#endif
// STL includes
#include <stdio.h>
// other includes
#include "Point.h"

void init_gnuplot();
void plot_from(const char* filename, const char* options);
void plot(const Point* points, uint length, const char* options);
void plot_vector( const Point p1, const Point p2, const Vector normal, const char* options);
int close_gnuplot();

#ifdef __cplusplus
}
#endif

#endif
