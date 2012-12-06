#include "solver.hpp"

static const Point* p1 = NULL;
static const Point* p2 = NULL;
static const Point* pi = NULL;
static const Vector* n = NULL;

static double lambda_neumann(double x)
{
	const double alpha = (p2->y - p1->y) / (p2->x - p1->x);
	const double beta = p1->y - alpha*p1->x;
	const double X = x;
	const double Y = alpha*x + beta;
	const Point p = {.x = X, .y= Y, .z = 0};
	const Vector q = Point_sub(&p, pi);
	return -(1 / square(norm(&q)))*scalaire(&q, n);
}

static double lambda_dirichlet(double x)
{
	const double alpha = (p2->y - p1->y) / (p2->x - p1->x);
	const double beta = p1->y - alpha*p1->x;
	const double X = x;
	const double Y = alpha*x + beta;
	const Point p = {.x = X, .y = Y, .z = 0};
	const Vector q = Point_sub(&p, pi);
	return -log(sqrt(norm(&q)));
}

std::vector<double> solve(Domain& domega, Point* points)
{
	double h, g;
	uint i,j;
	std::vector<Condition_type> cond_type(domega.get_mesh_count());
	//std::vector<double> b(domega.get_mesh_count(), 0);
	double b[domega.get_mesh_count()];
	int ORDRE[domega.get_mesh_count()];
	double X[domega.get_mesh_count()];
	Matrice M(domega.get_mesh_count(), domega.get_mesh_count());
	i = 0;
	for (Domain::const_mesh_iterator it=domega.begin_mesh(); it != domega.end_mesh(); ++it)
	{
		p1 = &((*it)->get_p1());
		p2 = &((*it)->get_p2());
		n = &((*it)->get_normale());
		// \sum_{i=0}^n ...
		j = 0;
		for (Domain::const_mesh_iterator jt=domega.begin_mesh(); jt != domega.end_mesh(); ++jt)
		{
			pi = &((*jt)->get_center());
			h = integrate(p1->x, p2->x, lambda_neumann);
			g = integrate(p1->x, p2->x, lambda_dirichlet);
			if ((*it)->is_dirichlet()) // si l'inconnu est neumann
			{
				cond_type[i] = NEUMANN;
				b[i] -= g*(*it)->get_dirichlet_cond();
				M(i,j) = h-1;
				if (i == j)
				{
					--M(i,j);
				}
			}
			else if ((*it)->is_neumann())// l'inconnu est dirichlet
			{
				cond_type[i] = DIRICHLET;
				b[i] -= h*(*it)->get_neumann_cond();
				M(i,j) = g;
			}
			++j;
		}
		++i;
	}
	rsl_gauss_jordan(domega.get_mesh_count(),M,b,ORDRE,0,X);
	std::vector<double> ret(domega.get_mesh_count());
	for (uint i=0;i<ret.size();++i)
	{
		ret[i] = X[i];
	}
	return ret;
}
