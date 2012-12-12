#include "Mesh.hpp"
Mesh::Mesh(const Point* point_1, const Point* point_2, const Condition& condition) : p1(point_1), p2(point_2) 
{
	this->load_center();
	this->load_normal();
	
	this->dirichlet_cond = NULL;
	this->neumann_cond = NULL;
	
	if (condition.type == NEUMANN)
	{
		this->neumann_cond = new double(condition.value);
	}
	else if (condition.type == DIRICHLET)
	{
		this->dirichlet_cond = new double(condition.value);
	}
}

Mesh::~Mesh()
{
	if (this->neumann_cond != NULL)
	{
		delete this->neumann_cond;
	}
	if (this->dirichlet_cond != NULL)
	{
		delete this->dirichlet_cond;
	}
}

const Point& Mesh::get_p1()
{
	return *(this->p1);
}

const Point& Mesh::get_p2()
{
	return *(this->p2);
}

const Point& Mesh::get_center()
{
	return this->center;
}

const Vector& Mesh::get_normale()
{
	return this->normal;
}

const bool Mesh::is_dirichlet()
{
	return (this->dirichlet_cond) != NULL;
}

const bool Mesh::is_neumann()
{
	return (this->neumann_cond) != NULL;
}

double Mesh::get_dirichlet_cond()
{
	return *(this->dirichlet_cond);
}

double Mesh::get_neumann_cond()
{
	return *(this->neumann_cond);
}

void Mesh::load_center()
{
	set_point(
		&(this->center), 
		(this->p1->x + this->p2->x)/2, 
		(this->p1->y + this->p2->y)/2, 
		(this->p1->z + this->p2->z)/2
	);
	
}

void Mesh::load_normal()
{
	// différence finie dérivée seconde, puis normaliser.
	Vector p1p2 = Point_sub(this->p2, this->p1);
	double norm_p1p2 = norm(&p1p2);
	this->normal.x = (this->p2->y - this->p1->y) / norm_p1p2;
	this->normal.y = -(this->p2->x - this->p1->x) / norm_p1p2;
}
