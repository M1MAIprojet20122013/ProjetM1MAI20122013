#include "BoundaryManager.hpp"

BoundaryManager::BoundaryManager(const char* filename)
{
	std::ifstream input(filename, std::ifstream::in);
	if (!input.is_open())
	{
		std::cout << "[ERROR] couldn't open " << filename << std::endl; 
	}
	std::string line;
	
	uint boundary_index;
	char boundary_type[10];
	double boundary_value;
	
	Condition condition;
	
	for (uint i=1;!input.eof();++i)
	{
		getline(input, line);
		if (line[0] != '%' and line.size() != 0)
		{
			if (sscanf(line.c_str(), "%i %s %lf", &boundary_index, boundary_type, &boundary_value) != 3)
			{
				std::cout << "[ERROR] malformed expression at line : " << i << " in file : " << filename <<  std::endl;
			}
			else
			{
				if (strcmp(boundary_type, "DPHI_DN") == 0)
				{
					condition.type = NEUMANN;
				}
				else
				{
					condition.type = DIRICHLET;	
				}
				condition.value = boundary_value;
				
				this->insert(std::pair<uint, Condition>(boundary_index, condition));
			}
		}
	}
}

Condition& BoundaryManager::get_condition(uint group_id)
{
	if (this->find(group_id) == this->end())
	{
		std::cout << "[ERROR] the requested boundary condition " << group_id << " doesn't exist" << std::endl;
	}
	return this->operator[](group_id);
}
