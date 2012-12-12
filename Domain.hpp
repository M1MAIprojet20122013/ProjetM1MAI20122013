#ifndef DOMAINE_HPP
#define DOMAINE_HPP

// STL includes
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
// other includes
#include "commun.h"
#include "Point.h"
#include "Mesh.hpp"
#include "Condition.h"
#include "BoundaryManager.hpp"

class Domain
{
public:
	typedef std::vector<Point>::const_iterator const_point_iterator;
	typedef std::vector<Mesh*>::const_iterator const_mesh_iterator;
	
	Domain(const char* filename, BoundaryManager& boundary_manager); // charge le domaine depuis un .mesh
	~Domain();
	
	uint get_mesh_count();
	uint get_point_count();

	const_point_iterator begin_point();
	const_point_iterator end_point();

	const_mesh_iterator begin_mesh();
	const_mesh_iterator end_mesh();

	void save(const char* filename);
protected:
private:
	std::vector<Point> points;
	std::vector<Mesh*> mesh;
};

#endif
