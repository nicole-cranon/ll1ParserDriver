/*
	nicole cranon <nicole.cranon@ucdenver.edu>
	csci 4640, fall 2015
	assignment 8 - ll1 parser driver
 */

#include "driver.h"
#include "helper.h"
#include "predictGenerator.h"
#include "grammerAnalyzer.h"

int main (int argc, char* argv[]) {
	if (argc < 3) {
		std::cerr << "\nNot enough arguments provided!\n";
		std::cerr << "\nCorrect input is [executable] [grammerFile] [tableFile] [program]\n";
		return 0;
	}

	const char* grammerFile = argv[1];
	const char* tableFile = argv[2];
	const char* program = argv[3];

	std::vector<std::string> ingrammer, 
		outgrammer,
		RHSList,
		LHSList;

	std::set<std::string> nonterminals,
		terminals,
		symbols;

	ga::read_productions (grammerFile, ingrammer);

	ga::analyze (ingrammer, outgrammer, nonterminals, terminals, symbols, 
			LHSList, RHSList);

	helper::ridSpaces (nonterminals, terminals, symbols, LHSList, RHSList);

	auto RHSStringList = predict::getRHS_stringList (RHSList);


	// program := the program to be read
	scanner::infile.open (program);

	const char* const transitionTable = "./transitionTable";
	scanner::readTransitionTable (transitionTable, scanner::T, scanner::terminalState);

	const char* const actionTable = "./actionTable";
	scanner::readActionTable (actionTable);

	std::map<std::string, std::map<std::string, unsigned>> T;
	driver::getTable (T, tableFile);

	// for (auto nt : T) {
	// 	for (auto t : nt.second) {
	// 		std::cout << nt.first << ' ' << t.first << ' ' << t.second << '\n';
	// 	}
	// }

	driver::llDriver (T, nonterminals, terminals, LHSList, RHSStringList);

	scanner::infile.close ();
	return 0;
}