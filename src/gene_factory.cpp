#include <cstring>
#include <cctype>
#include <cassert>
#include <chrono>
#include <random>
#include <cassert>
#include <utility>

#include "gene_factory.hpp"
#include "GeneticsSimDataParser.hpp"

// Staic vars
std::vector<gene_metadata> gene_factory::_metadata; // static metadata. 
int gene_factory::_crossover_count = 0;

gene_factory::gene_factory() {}

gene_factory* gene_factory::get_instance() {
	static gene_factory* theInstance = nullptr;
	if(theInstance == nullptr) {
		theInstance = new gene_factory();
	}
	return theInstance;
}

void gene_factory::read_from_file(std::string file) {
	// Assuming that we're configuring this in simulation. 
	auto parser = GeneticsSimDataParser::get_instance();

	char buffer0[256] = {0};
	char buffer1[256] = {0};
	char buffer2;
	char buffer3[256] = {0};
	char buffer4;
	double co_chance;

	// Create metadata for each gene data thing. 
	while(parser->getGeneData(buffer0, buffer1, &buffer2, buffer3, &buffer4, &co_chance)) {
		// Read the metadata from file
		std::string trait(buffer0);
		std::string dom_desc(buffer1);
		char domSymbol = buffer2;
		std::string rec_desc(buffer3);
		char recSymbol = buffer4;

		// Stuff it into a new object. 
		// Also, call move on all the buffer data. No need to waste cycles!
		gene_metadata m_data(std::move(trait),
							 domSymbol, std::move(dom_desc),
							 recSymbol, std::move(rec_desc),
							 co_chance);

		_metadata.push_back(std::move(m_data));

		// Lazily clear the buffers. 
		memset(buffer0, 0, sizeof(buffer0));
		memset(buffer1, 0, sizeof(buffer1));
		memset(buffer3, 0, sizeof(buffer3));
	}
}

std::pair<gene, bool> gene_factory::breed(std::pair<gene, bool>& g1, std::pair<gene, bool>& g2) {
	// Only this function cares about random generators. So we don't 
	// Muddle other people's code. 
	static auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	static std::mt19937 rd(seed);
    static std::uniform_real_distribution<> dist(0.0, 1.0);
    static std::uniform_real_distribution<> percent_dist(0.0, 100.0);

    // MAKE SURE WE CAN BREED
    assert(g1.first.can_breed_with(g2.first));

    std::pair<allele, allele> gene1_pair = gene::genotype_to_pair(g1.first._geno);
    std::pair<allele, allele> gene2_pair = gene::genotype_to_pair(g2.first._geno);

    if(g1.second == false) 
    	std::swap(gene1_pair.first, gene1_pair.second);
    if(g2.second == false) 
    	std::swap(gene2_pair.first, gene2_pair.second);

    // test for swapover. 
    // and swap if crossed. 
    bool crossed = false;
    if(percent_dist(rd) < g1.first._metadata->get_crossover_chance()) {
    	std::swap(gene1_pair.first, gene1_pair.second);
    	crossed = true;
    }
    // swap if crossed. 
    if(percent_dist(rd) < g2.first._metadata->get_crossover_chance()) {
    	std::swap(gene2_pair.first, gene2_pair.second);	
    	crossed = true;
    }
    if(crossed)
    	_crossover_count++;

    // pick new gene randomly.
    allele new_first = (dist(rd) < 0.5) ? gene1_pair.first : gene1_pair.second;
    // pick new gene2 randomly
    allele new_second = (dist(rd) < 0.5) ? gene2_pair.first : gene2_pair.second;

    // Calculate new genotype. 
	genotype new_geno = gene::pair_to_genotype(new_first, new_second);
	g1.first._metadata->increment_genotype(new_geno); // record in metadata. 
	// And the orientation
	bool ori = (new_geno == genotype::heterozygous_dominant) ? (new_first == allele::dominant) : true;

	// Copy prevented due to copy elision :)
    return std::make_pair(gene(new_geno, g1.first._metadata), ori);
}

gene gene_factory::create(char trait1, char trait2) {

	assert(tolower(trait1) == tolower(trait2));

	// Get a gene metadata. 
	for(auto& md : _metadata) {
		if(trait1 == md.get_recessive_char() || trait1 == md.get_dominant_char()) {
			genotype geno = md.parse_pair(trait1, trait2);
			return gene(geno, &md); // return genotype/metadata gene
		}
	}

	// Something went wrong and we didn't find metadata. 
	return gene();
}

void gene_factory::print_metadata(std::ostream& os) {
	static std::string tab("\t");

	os << "Gene metadata read from file: " << std::endl;
	for(auto& gm : _metadata) {
		gm.format_print(os, tab);
	}
}

void gene_factory::print_results(std::ostream& os) {
	static std::string empty("");

	for(auto& gm : _metadata) 
		gm.print_results(os, empty);

	std::cout << std::endl;
	std::cout << "A total of " << _crossover_count << " offspring had at least one crossover gene.";
	std::cout << std::endl << std::endl;
}
