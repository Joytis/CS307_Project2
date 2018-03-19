#include "chromosome.hpp"

chromosome::chromosome() {} // do nothing. 
chromosome::chromosome(std::vector<std::pair<gene, bool>>&& genes) 
	: _genes(genes)
{}

void chromosome::format_print(std::ostream& os, std::string& title, std::string& line_start) {
	os << line_start << title << std::endl;
	for(auto& g_pair : _genes) {
		gene& g = g_pair.first;
		os << line_start << "\t\tGene Type = " << g.get_trait() << std::endl 
		   << line_start << "\t\t\tGenotype = " << g.get_genotype_string() << std::endl;
	}
}