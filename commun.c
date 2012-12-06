#include "commun.h"

#define integrate_x0 -sqrt((3.0-2.0*sqrt(6.0/5.0))/7.0) 
#define integrate_w0 (18.0 + sqrt(30.0)) / 36.0
#define integrate_x1 +sqrt((3.0-2.0*sqrt(6.0/5.0))/7.0) 
#define integrate_w1 (18.0 + sqrt(30.0)) / 36.0
#define integrate_x2 -sqrt((3.0+2.0*sqrt(6.0/5.0))/7.0)
#define integrate_w2 (18.0 - sqrt(30.0)) / 36.0
#define integrate_x3 +sqrt((3.0+2.0*sqrt(6.0/5.0))/7.0) 
#define integrate_w3 (18.0 - sqrt(30.0)) / 36.0

//~ static double integrate_w[] = {(18 + sqrt(30)) / 36, (18 + sqrt(30)) / 36, (18 - sqrt(30)) / 36, (18 - sqrt(30)) / 36};
//~ static double integrate_x[] = {-sqrt((3-2*sqrt(6/5))/7), sqrt((3-2*sqrt(6/5))/7), -sqrt((3+2*sqrt(6/5))/7), sqrt((3+2*sqrt(6/5))/7)};

double integrate(double a, double b, double (*f)(double x))
{
	return 0.5*(b - a)*(integrate_w0*f((integrate_x0*(b-a) / 2.0) + ((a + b) / 2.0)) 
		+ integrate_w1*f((integrate_x1*(b-a) / 2.0) + ((a + b) / 2.0))
		+ integrate_w2*f((integrate_x2*(b-a) / 2.0) + ((a + b) / 2.0))
		+ integrate_w3*f((integrate_x3*(b-a) / 2.0) + ((a + b) / 2.0)));
}
