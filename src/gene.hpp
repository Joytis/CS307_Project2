/*******************************************************************
*   gene.hpp
*   project1_307
*   Author: Clark Chambers
*   Date: 2018-02-16
*   
*   This program is entirely my own work
*******************************************************************/

#pragma once

#include <unordered_map>

#include "gene_metadata.hpp"

class gene {
	// We control this. 
	friend struct std::hash<gene>;
	friend class gene_factory;

private:
	genotype _geno;
	gene_metadata* _metadata;


public:
	static std::pair<allele, allele> genotype_to_pair(genotype geno);
	static genotype pair_to_genotype(allele a1, allele a2);

	gene();
	gene(genotype geno, gene_metadata* meta);

	std::string get_genotype_string() const;
	std::string get_trait() const;
	genotype get_genotype() const;
	char get_dominant_char() const;
	char get_recessive_char() const;

	bool can_breed_with(gene& other);

};