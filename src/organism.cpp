/*******************************************************************
*   organism.cpp
*   project1_307
*   Author: Clark Chambers
*   Date: 2018-02-16
*   
*   This program is entirely my own work
*******************************************************************/


#include "organism.hpp"
#include "organism_metadata.hpp"
#include "organism_factory.hpp"


#include <sstream>
#include <iterator>
#include <algorithm>
#include <iostream>	
#include <functional>

organism::organism() {} // do nothing. 

organism::organism(std::vector<chromosome>&& chromes)
	: _chromosomes(chromes)
{} // do nothing;

void organism::format_print(std::ostream& os, std::string& title) {
	static std::string tabs("\t\t");

	auto& meta = organism_factory::get_metadata();
	os << title << std::endl
	   << "\tOrganism genus-species: " << meta.get_genus() << std::endl
	   << "\tCommon name: " << meta.get_common_name() << std::endl
	   << "\tGenes: " << std::endl;

   // Print all chromosomes
	for(int i = 0; i < _chromosomes.size(); i++) {
		std::string title("Chromosome ");
		title += std::to_string(i);

		_chromosomes[i].format_print(os, title, tabs);
	}
}