#include "solver.hpp"
#include "plot.h"
#include <iostream>

static double lambda_dirichlet(Point x,Point pi, Vector n)
{
	const Vector q = Point_sub(&x, &pi);
	return -(1 / square(norm(&q)))*scalaire(&q, &n);
}

static double lambda_neumann(Point x,Point pi)
{
	const Vector q = Point_sub(&x, &pi);
	return -log(sqrt(norm(&q)));
}

std::vector<double> solve(Domain& domega, Point* points)
{

	 Point p1,pc,p2,pi;
	 Vector n;
	double h, g;
	uint i,j,taille = domega.get_mesh_count();

	static const double integrate_w[] = {(18 + sqrt(30)) / 36, (18 + sqrt(30)) / 36, (18 - sqrt(30)) / 36, (18 - sqrt(30)) / 36};
	static const double integrate_x[] = {-sqrt((3-2*sqrt(6/5))/7), sqrt((3-2*sqrt(6/5))/7), -sqrt((3+2*sqrt(6/5))/7), sqrt((3+2*sqrt(6/5))/7)};
	std::vector<Condition_type> cond_type(taille);
	//std::vector<double> b(taille, 0);
	double b[taille];
	int ORDRE[taille];
	double X[taille];
	Matrice M(taille, taille);

	i = 0;
	for (Domain::const_mesh_iterator it=domega.begin_mesh(); it != domega.end_mesh(); ++it)
	{
		b[i] = 0;
		p1 = (*it)->get_p1();
		p2 = (*it)->get_p2();
		pc = (*it)->get_center();
		n = (*it)->get_normale();
		// \sum_{i=0}^n ...
		j = 0;
		for (Domain::const_mesh_iterator jt=domega.begin_mesh(); jt != domega.end_mesh(); ++jt)
		{
			h=0;
			g=0;
			pi = ((*jt)->get_center());
			//n = ((*jt)->get_normale());
			for(uint k =0;k<4;++k){
				Point xk = {pc.x + integrate_x[k] * 0.5* (p2.x-p1.x),pc.y + integrate_x[k] * 0.5* (p2.y-p1.y)};
				g += integrate_w[k]*lambda_neumann(xk, pi);
				h += integrate_w[k]*lambda_dirichlet(xk,pi,n);
			}
			std::cout << "hij = " << h <<std::endl;
			std::cout << "gij = " << g <<std::endl;
			if ((*it)->is_dirichlet()) // si l'inconnu est neumann
			{
				cond_type[i] = NEUMANN;
				b[i] -= g*(*it)->get_dirichlet_cond();
				M(i,j) = h;
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
			M(i,j) /= 3.1417;
			++j;
		}

		++i;
	}
	rsl_gauss_jordan(taille,M,b,ORDRE,0,X);
	std::vector<double> ret(taille);
	for (uint i=0;i<taille;++i)
	{
		ret[i] = X[i];
	}
	return ret;
}
