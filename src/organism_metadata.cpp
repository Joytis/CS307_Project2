/*******************************************************************
*   organism_metadata.cpp
*   project1_307
*   Author: Clark Chambers
*   Date: 2018-02-16
*   
*   This program is entirely my own work
*******************************************************************/


#include "organism_metadata.hpp"
#include "organism.hpp"

#include <algorithm>

organism_metadata::organism_metadata(std::string&& genus, std::string&& species, 
								     std::string&& common_name, std::string&& sci_name)
	: _genus(genus), _species(species), _common_name(common_name), 
	  _sci_name(sci_name) // _genotype_meta(genotype_meta)
{} // do nothing. 

organism_metadata::organism_metadata() {} // do nothing. 

std::string organism_metadata::get_genus() const { return _genus; }
std::string organism_metadata::get_species() const { return _species; }
std::string organism_metadata::get_common_name() const { return _common_name; }
std::string organism_metadata::get_sci_name() const { return _sci_name; }