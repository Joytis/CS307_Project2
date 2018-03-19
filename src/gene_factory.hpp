#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "gene.hpp"
#include "genotype.hpp"
#include "gene_metadata.hpp"

class gene_factory {
private:
	static std::vector<gene_metadata> _metadata; // static metadata. 
	static int _crossover_count;

	gene_factory();
public:
	// Used to initialize the static system
	static gene_factory* get_instance(); // Instance
	static std::pair<gene, bool> breed(std::pair<gene, bool>& o1, std::pair<gene, bool>& o2);
	static void print_metadata(std::ostream& os);
	static void print_results(std::ostream& os);
	void read_from_file(std::string file);
	gene create(char trait1, char trait2);
};