#ifndef BOUNDARY_MANAGER_HPP
#define BOUNDARY_MANAGER_HPP

#include "Condition.h"

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cassert>

class BoundaryManager : private std::map<uint,Condition>
{
public:
	BoundaryManager(const char* filename);
	Condition& get_condition(uint group_id);
};

#endif
