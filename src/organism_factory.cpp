#include <cstring>
#include <cassert>

#include "organism_factory.hpp"
#include "chromosome_factory.hpp"
#include "GeneticsSimDataParser.hpp"

organism_metadata organism_factory::_metadata;
int organism_factory::parent_count = 0;

organism_factory::organism_factory() {}

organism_factory* organism_factory::get_instance() {
	static organism_factory* theInstance = nullptr;
	if(theInstance == nullptr) {
		theInstance = new organism_factory();
	}
	return theInstance;
}

const organism_metadata& organism_factory::get_metadata(){
	return organism_factory::_metadata;
}


organism organism_factory::breed(organism& o1, organism& o2) {
	// Breed those dudes together. 
	assert(o1._chromosomes.size() == o2._chromosomes.size());

	auto& chromes1 = o1._chromosomes;
	auto& chromes2 = o2._chromosomes;

	vector<chromosome> chromes;
	for(size_t i = 0; i < chromes1.size(); i++) {
		chromes.push_back(chromosome_factory::breed(chromes1[i], chromes2[i]));
	}

	return organism(std::move(chromes));
}

void organism_factory::read_from_file(std::string file) {
	// Assuming that we're configuring this in simulation. 
	auto parser = GeneticsSimDataParser::get_instance();

	// Parse organism metadata.
	std::string genus(parser->getGenus());
	std::string species(parser->getSpecies());
	std::string sci_name(parser->getScientificName());
	std::string common_name(parser->getCommonName());

	_metadata = organism_metadata(std::move(genus), std::move(species),
								  std::move(common_name), std::move(sci_name));

	parent_count = 0; // Haven't read any parents from the file. 
}

organism organism_factory::get_parent() {


	if(parent_count >= 2) {
		return organism();
	}

	auto parser = GeneticsSimDataParser::get_instance();
	int chromo_count = parser->getChromosomeCount();
	auto chrome_factory = chromosome_factory::get_instance();

	// make some empty buffers for reading. 
	char buffer0[256] = {0};
	char buffer1[256] = {0};

	std::vector<chromosome> chromosomes; 
	if (parent_count == 1) {

		// Get all the chromosome strings. 
		while(parser->getP2Chromosome(buffer0, buffer1)) {
			std::string strand1(buffer0);
			std::string strand2(buffer1);

			chromosome c = chrome_factory->create(std::move(strand1), std::move(strand2));
			chromosomes.push_back(std::move(c));

			// Clear buffers. I'm lazy here. 
			memset(buffer0, 0, sizeof(buffer0));
			memset(buffer1, 0, sizeof(buffer1));
		}
	}
	else if(parent_count == 0) { 
		while(parser->getP1Chromosome(buffer0, buffer1)) {
			std::string strand1(buffer0);
			std::string strand2(buffer1);

			chromosome c = chrome_factory->create(std::move(strand1), std::move(strand2));
			chromosomes.push_back(std::move(c));

			// Clear buffers. I'm lazy here. 
			memset(buffer0, 0, sizeof(buffer0));
			memset(buffer1, 0, sizeof(buffer1));
		}
	}

	parent_count++;

	return organism(std::move(chromosomes));
}