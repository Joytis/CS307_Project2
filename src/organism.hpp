/*******************************************************************
*   organism.hpp
*   project1_307
*   Author: Clark Chambers
*   Date: 2018-02-16
*   
*   This program is entirely my own work
*******************************************************************/


#pragma once

#include <string>
#include <vector>
#include <algorithm>

// #include "gene.hpp"
#include "chromosome.hpp"

class organism_metadata; // forward declaration

class organism {
	// We control this. 
	friend struct std::hash<organism>;
	friend class organism_factory;

private:
	std::vector<chromosome> _chromosomes;

public:
	organism(); // default constructor. 
	organism(std::vector<chromosome>&& chromes); // constructor. 

	void format_print(std::ostream& os, std::string& title);
};