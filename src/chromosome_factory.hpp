#pragma once

#include <string>
#include <vector>

#include "chromosome.hpp"

class chromosome_factory {
private:
	// static organism_metadata _metadata; // static metadata. 
	// std::vector<chromosome> 

	chromosome_factory();
public:
	// Used to initialize the static system
	static chromosome_factory* get_instance(); // Instance
	static chromosome breed(chromosome& o1, chromosome& o2);
	chromosome create(std::string strand1, std::string strand2);

};