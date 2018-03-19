#pragma once

#include <string>

#include "organism.hpp"
#include "organism_metadata.hpp"

class organism_factory {

private:
	static organism_metadata _metadata; // static metadata. 
	static int parent_count;

	organism_factory();
public:
	// Used to initialize the static system
	static organism_factory* get_instance(); // Instance
	static organism breed(organism& o1, organism& o2);
	void read_from_file(std::string file);
	organism get_parent();

	static const organism_metadata& get_metadata();
};