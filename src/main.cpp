/*******************************************************************
*   main.cpp
*   project1_307
*   Author: Clark Chambers
*   Date: 2018-02-16
*   
*   This program is entirely my own work
*******************************************************************/
#include "simulation.hpp"	
#include "organism_factory.hpp"
#include "gene_factory.hpp"
#include "GeneticsSimDataParser.hpp"

int main(int argc, const char** argv) {

	simulation sim;

	// get file from user. 
	std::string filepath;
	std::cout << "While file would you like to read?" 
			  << "(Type the file path and press Enter) " << std::endl << "==>";
	cin >> filepath;

	sim.setup(filepath);

	sim.print_master_info(std::cout);
	sim.print_parent_info(std::cout);

	// Query for user input with trials. 
	size_t num_trials;
	std::cout << "How many offspring do you want to generate?"
			  << " (Type the number then press Enter)" << std::endl << "==>";
	std::cin >> num_trials;

	sim.run(num_trials);

	sim.print_results(std::cout);

    return 0;
}
