#ifndef POINT_H
#define POINT_H

#ifdef __cplusplus
extern "C"
{
#endif

// STL includes
#include <math.h>
// other includes
#include "commun.h"

typedef struct s_Point Point;
typedef Point Vector;

struct s_Point
{
	double x;
	double y;
	double z;
};

Point new_point(double x, double y, double z);

void set_point(Point* p, double x, double y, double z);
double d(const Point* p1, const Point* p2);

double scalaire(const Vector* v1, const Vector* v2);
double norm(const Vector* v);

Point Point_add(const Point* p1, const Point* p2);
Point Point_sub(const Point* p1, const Point* p2);
Point Point_mul(const Point* p1, const Point* p2);
Point Point_div(const Point* p1, const Point* p2);

#ifdef __cplusplus
}
#endif

#endif
