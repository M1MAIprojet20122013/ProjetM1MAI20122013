#ifndef MESH_HPP
#define MESH_HPP

#include <stddef.h>

#include "commun.h"
#include "Point.h"
#include "Condition.h"

class Mesh
{
public:
	Mesh(const Point* point_1, const Point* point_2, Condition* cond);
	~Mesh();
	// getter/setter
	const Point& get_p1();
	const Point& get_p2();
	const Point& get_center();	
	const Vector& get_normale();
	
	const bool is_neumann();
	const bool is_dirichlet();

	double get_dirichlet_cond();
	double get_neumann_cond();
protected:
	void load_center();
	void load_normal();

	const Point* p1;
	const Point* p2;
	Point center;
	Vector normal;
	double* dirichlet_cond;
	double* neumann_cond;
private:
};

#endif
