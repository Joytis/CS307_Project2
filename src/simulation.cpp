/*******************************************************************
*   simulation.cpp
*   project1_307
*   Author: Clark Chambers
*   Date: 2018-02-16
*   
*   This program is entirely my own work
*******************************************************************/


#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

#include "simulation.hpp"
#include "organism_factory.hpp"
#include "chromosome_factory.hpp"
#include "gene_factory.hpp"
#include "GeneticsSimDataParser.hpp"

// Do nothing. 
simulation::simulation() {}

bool simulation::setup(std::string filepath) {
	// Spin up a Coleman parser and snag some info from it. 
	GeneticsSimDataParser* parser = GeneticsSimDataParser::get_instance();
	parser->initDataFile(const_cast<char*>(filepath.c_str()));

	// Parse organism metadata.
	auto org_factory = organism_factory::get_instance();
	auto chrome_factory = chromosome_factory::get_instance();
	auto gene_factory = gene_factory::get_instance();

	org_factory->read_from_file(filepath);
	// chrome_factory->read_from_file(filepath);
	gene_factory->read_from_file(filepath);

	// // Setup the parents...
	_parent1 = org_factory->get_parent(); // org data lifetime is same as parent, so it's cool. 
	_parent2 = org_factory->get_parent(); // org data lifetime is same as parent, so it's cool. 
}

void simulation::run(size_t trials) {
	// NO MORE THAN 1000 TRIALS
	if(trials > 1000) 
		trials = 1000;

	// Appent a bunch of children. 
	_children.clear();
	// _organism_counts.clear();

	for(int i = 0; i < trials; i++) 
		_children.push_back(organism_factory::breed(_parent1, _parent2));
}


void simulation::print_master_info(std::ostream& os) {
	gene_factory::print_metadata(os);
}
void simulation::print_parent_info(std::ostream& os) {
	static std::string parent_title_1("Sim parent 1");
	static std::string parent_title_2("Sim parent 2");
	_parent1.format_print(os, parent_title_1);
	os << std::endl;
	_parent2.format_print(os, parent_title_2);
	os << std::endl;
}

void simulation::print_results(std::ostream& os) {

	os << "======================= Results of this Run =======================" << std::endl << std::endl;

	gene_factory::print_results(os);
}	