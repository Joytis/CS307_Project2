/*******************************************************************
*   gene.cpp
*   project1_307
*   Author: Clark Chambers
*   Date: 2018-02-16
*   
*   This program is entirely my own work
*******************************************************************/

#include "gene.hpp"

#include <random> 
#include <chrono>

gene::gene() {} // do nothing
gene::gene(genotype geno, gene_metadata* meta) 
	: _geno(geno), _metadata(meta)
{}

static std::unordered_map<genotype, std::pair<allele, allele>> _create_table() {
	std::unordered_map<genotype, std::pair<allele, allele>> table;
	table[genotype::homozygous_dominant] = std::make_pair(allele::dominant, allele::dominant);
	table[genotype::heterozygous_dominant] = std::make_pair(allele::dominant, allele::recessive);
	table[genotype::homozygous_recessive] = std::make_pair(allele::recessive, allele::recessive);
	return table;
}

genotype gene::pair_to_genotype(allele a1, allele a2) {
	if(a1 == allele::dominant && a2 == allele::dominant) {
		return genotype::homozygous_dominant;
	}
	if(a1 == allele::recessive && a2 == allele::recessive) {
		return genotype::homozygous_recessive;
	}
	return genotype::heterozygous_dominant;
}


std::pair<allele, allele> gene::genotype_to_pair(genotype geno) {
	// Still no initializer lists in msvc :'c
	static std::unordered_map<genotype, std::pair<allele, allele>> table = _create_table();

	// create allales from the genotypes 
    return table[geno];
}
	

std::string gene::get_genotype_string() const {
	// Make sure to order such that greatest comes first. 
	std::string ret_val = "";
	// Homozygus dominant
	switch(_geno) {
		case genotype::homozygous_dominant:
			ret_val += _metadata->get_dominant_char();
			ret_val += _metadata->get_dominant_char();
			break;
		case genotype::heterozygous_dominant:
			ret_val += _metadata->get_dominant_char();
			ret_val += _metadata->get_recessive_char();
			break;
		case genotype::homozygous_recessive:
			ret_val += _metadata->get_recessive_char();
			ret_val += _metadata->get_recessive_char();
			break;
	}

	// Copy prevented due to copy elision :)
	return ret_val;
}

std::string gene::get_trait() const { return _metadata->get_trait(); }
genotype gene::get_genotype() const { return _geno; }
char gene::get_dominant_char() const { return _metadata->get_dominant_char(); }
char gene::get_recessive_char() const { return _metadata->get_recessive_char(); }

bool gene::can_breed_with(gene& other) {
	return _metadata == other._metadata;
}