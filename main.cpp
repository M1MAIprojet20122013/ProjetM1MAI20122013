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
	BoundaryManager boundary_manager("boundary_settings.conf");	
	Domain domega("carre_mais_mieux.msh", boundary_manager);
	domega.save("domega.txt");
	init_gnuplot();
	 Point points[3];
	 for (Domain::const_mesh_iterator it=domega.begin_mesh();it != domega.end_mesh();++it)
	 {
	     points[0] = (*it)->get_p1();
	     points[1] = (*it)->get_center();
	     points[2] = (*it)->get_p2();
	     plot(points, 3, "with linespoints");
	     plot_vector((*it)->get_p1(),(*it)->get_p2(), (*it)->get_normale(),"using 1:2:3:4 with vectors head filled lt 2");
	     // pour plot en 3D un vecteur:
	    //~ // splot 'file.dat' using 1:2:3:4:5:6 with vectors filled head lw 2
	    //~ //((*it)->is_dirichlet()) ? cout << "dirichlet = " << (*it)->get_dirichlet_cond() <<endl : cout << "neumann = " << (*it)->get_neumann_cond() <<endl; 
	}
	close_gnuplot();
	std::vector<double> ret = solve(domega, NULL);
	for(uint i =0;i<ret.size();++i)
	  cout << i << "\t" <<  ret[i] << endl;
	  
	  
	  
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
