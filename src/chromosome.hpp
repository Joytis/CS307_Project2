#pragma once

#include <vector>
#include <unordered_map>
#include "gene.hpp"

class chromosome {
	friend class chromosome_factory;

private:

	// genes have their orientation stapled to them. 
	// True represents first allele on first strand. 
	// False represents second allele on the first strand. 
	std::vector<std::pair<gene, bool>> _genes;

public:

	chromosome();
	chromosome(std::vector<std::pair<gene, bool>>&& genes);

	void format_print(std::ostream& os, std::string& title, std::string& line_start);
};