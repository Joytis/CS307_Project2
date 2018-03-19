#include "chromosome_factory.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cassert>


#include "gene_factory.hpp"
#include "genotype.hpp"
#include "GeneticsSimDataParser.hpp"

// organism_metadata organism_factory::_metadata;

chromosome_factory::chromosome_factory() {}

chromosome_factory* chromosome_factory::get_instance() {
	static chromosome_factory* theInstance = nullptr;
	if(theInstance == nullptr) {
		theInstance = new chromosome_factory();
	}
	return theInstance;
}

chromosome chromosome_factory::breed(chromosome& c1, chromosome& c2) {
	// Breed those dudes together. 
	assert(c1._genes.size() == c2._genes.size());

	auto& genes1 = c1._genes;
	auto& genes2 = c2._genes;

	std::vector<std::pair<gene, bool>> genes;
	for(int i = 0; i < genes1.size(); i++) {
		auto g = gene_factory::breed(genes1[i], genes2[i]);
		genes.push_back(std::move(g));
	}

	return chromosome(std::move(genes));
}

chromosome chromosome_factory::create(std::string strand1, std::string strand2) {
	// WARN(clark): This may break msvc?
	// Split the strands into split characters 
	std::istringstream iss1(strand1);
	std::vector<char> strand1_chars;
	std::copy(std::istream_iterator<char>(iss1),
		      std::istream_iterator<char>(),
		      std::back_inserter(strand1_chars));

	std::istringstream iss2(strand2);
	std::vector<char> strand2_chars;
	std::copy(std::istream_iterator<char>(iss2),
		      std::istream_iterator<char>(),
		      std::back_inserter(strand2_chars));


	// Create the actual gene!
	assert(strand1_chars.size() == strand2_chars.size());

	auto g_factory = gene_factory::get_instance();

	std::vector<std::pair<gene, bool>> genes;
	for(int i = 0; i < strand1_chars.size(); i++) {

		char ch1 = strand1_chars[i];
		char ch2 = strand2_chars[i];
		gene g = g_factory->create(ch1, ch2); // make gene. 

		bool orientation = true;
		// We only care about orientation if both alleles aren't the same. 
		if(g.get_genotype() == genotype::heterozygous_dominant) {
			// If the dominant character is here
			orientation = (g.get_dominant_char() == ch1);
		}
		genes.push_back(std::make_pair(g, orientation));
	}

	return chromosome(std::move(genes));
}