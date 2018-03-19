/*******************************************************************
*   gene_metadata.hpp
*   project1_307
*   Author: Clark Chambers
*   Date: 2018-02-16
*   
*   This program is entirely my own work
*******************************************************************/

#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

#include "allele.hpp"
#include "genotype.hpp"

class gene_metadata {

private:
	std::string 	_trait;
	char 			_dominant_char;
	std::string 	_dominant_phenotype;
	char 			_recessive_char;
	std::string 	_recessive_phenotype;
	double 			_crossover_chance;

	bool check_character(char c); // checks if character is either a dominant or recessive char. 

	std::unordered_map<genotype, int> _counts;

public:
	gene_metadata(std::string&& trait, 
				  char dom_char, std::string&& dom_desc,
				  char rec_char, std::string&& rec_desc,
				  double crossover_chance);

	std::string get_trait();
	std::string get_recessive_phenotype();
	std::string get_dominant_phenotype();
	char get_recessive_char();
	char get_dominant_char();
	double get_crossover_chance();

	void increment_genotype(genotype geno);
	int get_genotype_count(genotype geno);

	bool check_gene_pair(std::string& std); // check if gene pair is valid
	genotype parse_pair(std::string& str); //Parse into alleles. 
	genotype parse_pair(char t1, char t2); //Parse into alleles. 

	void print_results(std::ostream& os, std::string& line_start);
	void format_print(std::ostream& os, std::string& line_start) const;
	friend std::ostream& operator<<(std::ostream& os, const gene_metadata& m);
};