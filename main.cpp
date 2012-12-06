#include "Domain.hpp"
#include "plot.h"
#include "Point.h"
#include "commun.h"
#include "solver.hpp"
#include "Matrice.hpp"
#include "BoundaryManager.hpp"

#include <unistd.h>
#include <iostream>

#include <stdlib.h>
#include <math.h>

double f(double x)
{
	//return square(x-1);
	return log(x);
}

using namespace std;

int main()
{
	BoundaryManager bm("./boundary_settings.conf");	
	bm.get_condition(1);
	
	//~ Domain domega("../../../gmsh-2.6.2-svn-Linux/bin/toto.msh");
	//~ domega.save("/tmp/domega.txt");
	//~ init_gnuplot();
	//~ Point points[3];
	//~ for (Domain::const_mesh_iterator it=domega.begin_mesh();it != domega.end_mesh();++it)
	//~ {
	//~     points[0] = (*it)->get_p1();
	//~     points[1] = (*it)->get_center();
	//~     points[2] = (*it)->get_p2();
	//~     plot(points, 3, "with linespoints");
	//~ }
	//~ close_gnuplot();
	//~ solve(domega, NULL);
	
	//~ uint n = 1000;
	//~ Matrice m(n,n);
	//~ double b[n];
	//~ double X_0[n];
	//~ double X[n];
	//~ int ORDRE[n];
	//~ for (uint i=0;i<n;++i)
	//~ {
	//~ 	for (uint j=0;j<n;++j)
	//~ 	{
	//~ 		m(i,j) = static_cast<int>(ceil(rand())) % 10;
	//~ 	}
	//~ 	X_0[i] = i;
	//~ }
	//~ std::vector<double> temp = m*X_0;
	//~ for (uint i=0;i<temp.size();++i)
	//~ {
	//~ 	b[i] = temp[i];
	//~ }
	//~ cout << endl;
	//~ rsl_gauss_jordan(n, m, b, ORDRE, 0, X);
	//~ for (uint i=0;i<n;++i){cout << X[i] << "\t" << X_0[i]  << endl;}
	return 0;
}
