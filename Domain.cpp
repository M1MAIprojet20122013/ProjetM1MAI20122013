#include "./Domain.hpp"

Domain::Domain(const char* filename)
{
	std::ifstream input(filename);
	if (input.is_open())
	{
		// lecture des points
		std::string line;
		for (uint i=0;i<4;++i) // on lis les 4 premières lignes d'en-tête
		{
			getline(input, line);
		}
		uint count;
		uint index;
		uint i; 
		double x, y, z;
		input >> count;
		this->points = std::vector<Point>(count);
		for (i=0;i<count;++i)
		{
			input >> index >> x >> y >> z;
			set_point(&(this->points[i]), x, y, z);
		}
		// lecture des mesh
		for (i=0;i<3;++i) // on lis les 3 premières lignes d'en-tête
		{
			getline(input, line);
		}
		input >> count;
		this->mesh = std::vector<Mesh*>(count);
		uint p1_id, p2_id;
		Condition c;
		uint group_id; // identifie the bond
		for (i=0;i<count;++i)
		{
			input >> index >> index >> index >> group_id;
			input >> index >> p1_id >> p2_id;
			
			this->mesh[i] = new Mesh(&(this->points[p1_id-1]), &(this->points[p2_id-1]), &c);
		}
	}
	else
	{
		std::cerr << "Cannot open file " << filename << std::endl;
	}
}

Domain::~Domain()
{
	for (Domain::const_mesh_iterator it=this->mesh.begin();it != this->mesh.end();++it)
	{
		delete *it;
	}
}

uint Domain::get_mesh_count()
{
	return this->mesh.size();
}

uint Domain::get_point_count()
{
	return this->points.size();
}

Domain::const_point_iterator Domain::begin_point()
{
	return this->points.begin();
}

Domain::const_point_iterator Domain::end_point()
{
	return this->points.end();
}

Domain::const_mesh_iterator Domain::begin_mesh()
{
	return this->mesh.begin();
}

Domain::const_mesh_iterator Domain::end_mesh()
{
	return this->mesh.end();
}

void Domain::save(const char* filename)
{
	std::ofstream out;
	out.open(filename);
	for (Domain::const_point_iterator it = this->begin_point();it != this->end_point();++it)
	{
		out << it->x << " " << it->y << " " << it->z << std::endl;
	}
	out.close();
}

