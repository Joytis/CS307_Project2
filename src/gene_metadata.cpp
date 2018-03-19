/*******************************************************************
*   gene_metadata.cpp
*   path_to_file
*   Author: Clark Chambers
*   Date: 2018-02-05 16:24:03
*   
*   This program is entirely my own work
*******************************************************************/


#include "gene_metadata.hpp"
#include "gene.hpp"

gene_metadata::gene_metadata(std::string&& trait, 
						     char dom_char, std::string&& dom_desc,
						     char rec_char, std::string&& rec_desc,
						     double crossover_chance) :
	_trait(trait),
	_dominant_char(dom_char), _dominant_phenotype(dom_desc),
	_recessive_char(rec_char), _recessive_phenotype(rec_desc),
	_crossover_chance(crossover_chance)
{
	_counts[genotype::homozygous_dominant] = 0;
	_counts[genotype::homozygous_recessive] = 0;
	_counts[genotype::heterozygous_dominant] = 0;
}

std::string gene_metadata::get_trait() { return _trait; }
std::string gene_metadata::get_recessive_phenotype() { return _recessive_phenotype; }
std::string gene_metadata::get_dominant_phenotype() { return _dominant_phenotype; }
char gene_metadata::get_recessive_char() { return _recessive_char; }
char gene_metadata::get_dominant_char() { return _dominant_char; }
double gene_metadata::get_crossover_chance() { return _crossover_chance; }

bool gene_metadata::check_character(char c) {
	return (c == _recessive_char || c == _dominant_char);
}

bool gene_metadata::check_gene_pair(std::string& str) {
	// can't be a pair if it isn't size 2!
	if(str.size() != 2) 
		return false;

	// return validity. 
	return check_character(str[0]) && check_character(str[1]);
}

// Small data, so just return a copy.
// Requires input string to be valid and checked by gene pair. 
genotype gene_metadata::parse_pair(std::string& str) {
	allele first;
	allele second;

	// Parse first allele
	if(str[0] == _recessive_char) 
		first = allele::recessive;
	else 
		first = allele::dominant;

	// parse second allele
	if(str[1] == _recessive_char) 
		second = allele::recessive;
	else 
		second = allele::dominant;

	return gene::pair_to_genotype(first, second);

}

genotype gene_metadata::parse_pair(char t1, char t2) {
	allele first;
	allele second;

	// Parse first allele
	if(t1 == _recessive_char) 
		first = allele::recessive;
	else 
		first = allele::dominant;

	// parse second allele
	if(t2 == _recessive_char) 
		second = allele::recessive;
	else 
		second = allele::dominant;

	return gene::pair_to_genotype(first, second);
}

void gene_metadata::increment_genotype(genotype geno) {
	_counts[geno] += 1;
}

int gene_metadata::get_genotype_count(genotype geno) {
	return _counts[geno];
}

std::ostream& operator<<(std::ostream& os, const gene_metadata& md) {
	os << "Gene Metadata: " << std::endl 
	   << "Trait: " << md._trait << std::endl  
	   << "DominantChar: " << md._dominant_char << std::endl  
	   << "DominantPhenotype: " << md._dominant_phenotype << std::endl  
	   << "RecessiveChar: " << md._recessive_char << std::endl  
	   << "RecessivePhenotype: " << md._recessive_phenotype << std::endl
	   << "CrossoverChance: " << md._crossover_chance << std::endl;
	return os;
}

void gene_metadata::format_print(std::ostream& os, std::string& line_start) const {
	os << line_start << "Trait Name: " << _trait << std::endl
	   << line_start << "\tDominant Name: " << _dominant_phenotype 
	   										<< "(" << _dominant_char << ")" << std::endl
	   << line_start << "\tRecessive Name: " << _recessive_phenotype 
	   										<< "(" << _recessive_char << ")" << std::endl
	   << line_start << "\tChance of Crossover: " << _crossover_chance << std::endl;
}

void gene_metadata::print_results(std::ostream& os, std::string& line_start) {

	os << line_start << "Gene: " << _trait << std::endl;
	// Homo dominant
	os << line_start << '\t' << _counts[genotype::homozygous_dominant]
	   << line_start << " homozygous dominant "
	   << line_start << '(' << _dominant_phenotype << ' ' << _dominant_char << _dominant_char << ')' 
	   << line_start << std::endl;
	// Hetero dominant
	os << line_start << '\t' << _counts[genotype::heterozygous_dominant] 
	   << line_start << " heterozygous dominant "
	   << line_start << '(' << _dominant_phenotype << ' ' << _dominant_char << _recessive_char << ')' 
	   << line_start << std::endl;
	// Homo recessive. 
	os << line_start << '\t' << _counts[genotype::homozygous_recessive]
	   << line_start << " homozygous recessive "
	   << line_start << '(' << _recessive_phenotype << ' ' << _recessive_char << _recessive_char << ')' 
	   << line_start << std::endl << std::endl;
}