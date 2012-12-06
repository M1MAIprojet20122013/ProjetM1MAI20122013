#ifndef SOLVER_HPP
#define SOLVER_HPP

// STL includes
#include <vector>
#include <math.h>
// other includes
#include "Condition.h"
#include "Domain.hpp"
#include "Mesh.hpp"
#include "Point.h"
#include "commun.h"
#include "Matrice.hpp"

std::vector<double> solve(Domain& domega, Point* points);

#endif
