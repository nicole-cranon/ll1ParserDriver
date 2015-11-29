/*
	nicole cranon <nicole.cranon@ucdenver.edu>
	csci 4640, fall 2015
	assignment 8 - ll1 parser driver
 */

#ifndef _PARSER_DRIVER
#define _PARSER_DRIVER

#include "uscanner.h"
#include <set>
#include <vector>
#include <map>

namespace driver {
	void getTable (std::map<std::string, std::map<std::string, unsigned>>& T,
		const char *tableFile); 

	void llDriver (std::map<std::string, std::map<std::string, unsigned>>& T,
			const std::set<std::string>& nonterminals, 
			const std::set<std::string>& terminals,
			const std::vector<std::string>& LHS,
			const std::vector<std::vector<std::string> >& RHSList);

	void syntaxError ();

	unsigned getProduction (const std::vector<std::string>& LHS, const std::string& nonterminal);
};


#endif