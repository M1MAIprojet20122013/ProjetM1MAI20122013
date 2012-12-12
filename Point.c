#include "Point.h"

Point new_point(double x, double y, double z)
{
	Point p = {.x = x, .y = y, .z = z};
	return p;
}

double scalaire(const Vector* v1, const Vector* v2)
{
	return v1->x*v2->x + v1->y*v2->y + v1->z*v2->z;
}

double norm(const Vector* v)
{
	return sqrt(square(v->x) + square(v->y) + square(v->z));
}

void set_point(Point* p, double x, double y, double z)
{
	p->x = x;
	p->y = y;
	p->z = z;
}

double d(const Point* p1, const Point* p2)
{
	return sqrt(square(p1->x - p2->x) + square(p1->y - p2->y) + square(p1->z - p2->z));
}

Point Point_add(const Point* p1, const Point* p2)
{
	Point p3 = {.x=p1->x + p2->x, .y=p1->y + p2->y, .z=p1->z + p2->z};
	return p3;
}

Point Point_sub(const Point* p1, const Point* p2)
{
	Point p3 = {.x=p1->x - p2->x, .y=p1->y - p2->y, .z=p1->z - p2->z};
	return p3;
}

Point Point_mul(const Point* p1, const Point* p2)
{
	Point p3 = {.x=p1->x * p2->x, .y=p1->y * p2->y, .z=p1->z * p2->z};
	return p3;
}

Point Point_div(const Point* p1, const Point* p2)
{
	Point p3 = {.x=p1->x / p2->x, .y=p1->y / p2->y, .z=p1->z / p2->z};
	return p3;
}
