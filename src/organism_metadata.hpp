/*******************************************************************
*   organism_metadata.hpp
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
#include <unordered_map>

#include "gene_metadata.hpp"
#include "organism.hpp"

class organism; // forward declaration

class organism_metadata {

private:
	std::string _genus;
	std::string _species;
	std::string _common_name;
	std::string _sci_name;

public:
	// only accept moves for this constructor, because this should only be
	//		made during parsing of a file.
	organism_metadata();
	organism_metadata(std::string&& _genus, std::string&& _species, 
				      std::string&& _common_name, std::string&& _sci_name);

	std::string get_genus() const;
	std::string get_species() const;
	std::string get_common_name() const;
	std::string get_sci_name() const;
};