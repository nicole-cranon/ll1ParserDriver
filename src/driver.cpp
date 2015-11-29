/*
	nicole cranon <nicole.cranon@ucdenver.edu>
	csci 4640, fall 2015
	assignment 8 - ll1 parser driver
 */

#include "driver.h"
#include <stack>
#include <string>
#include <fstream>
#include <iostream>

namespace driver {

	void getTable (std::map<std::string, std::map<std::string, unsigned>>& T,
		const char *tableFile) {
		std::ifstream fRead;

		fRead.open (tableFile);

		std::string temp;
		bool readingLine = true;

		std::map<std::string, unsigned> terminalMap;

		// read terminals
		fRead >> temp;	// terminals label
		while (readingLine) {
			if (fRead.peek() == '\n') {
				readingLine = false;
				fRead.get ();
			} else {
				fRead >> temp;
				// std::cout << temp << ' ';
				terminalMap[temp] = 999;
			}
		}
		readingLine = true;
		// std::cout << "\n_______________________________\n";

		// for (auto t : terminalMap) {
		// 	std::cout << t.first << ' ' << t.second << '\n';
		// }

		unsigned production = 0;
		fRead >> temp;	// nonterminals label
		while (fRead.peek() != EOF) {
			fRead >> temp;
			// std::cout << temp << ' ';
			unsigned i = 0;
			for (auto t : terminalMap) {
				fRead >> production;
				// std::cout << production << ' ';
				T[temp][t.first] = production;
				++i;
			}
			fRead.get ();
			readingLine = true;
			// std::cout << '\n';
		}

		fRead.close();
	}

	void llDriver (std::map<std::string, std::map<std::string, unsigned>>& T,
			const std::set<std::string>& nonterminals, 
			const std::set<std::string>& terminals,
			const std::vector<std::string>& LHS,
			const std::vector<std::vector<std::string> >& RHSList) {
		std::stack<std::string,std::vector<std::string> > symbolStack;
		std::string X, 
			a, 
			parserAction, 
			symbol, 
			remainingInput;
		unsigned production,
			fileLoc;
		int tokenCode;
		const unsigned ERROR_CODE = 999;
		auto lhsItr = LHS.begin();
		std::vector<std::string> symbolStackV;
		
		symbolStack.push (*lhsItr);
		symbolStackV.push_back (*lhsItr);
		// std::cout << "\nStart Symbol->" << *lhsItr << '\n';

		/********************************************
			* Getting Remaining input
			*/
		fileLoc = scanner::infile.tellg ();
		scanner::infile.seekg (0, scanner::infile.end);
		char eof = scanner::infile.peek();
		scanner::infile.seekg (fileLoc);
		// std::cout << "\nPeek of End of File->" << eof;
		std::getline (scanner::infile, remainingInput, eof);
		if (remainingInput[remainingInput.size()-1] != eof) {
			remainingInput += eof;
		}
		scanner::infile.seekg (fileLoc);
		scanner::infile.clear();

		/**
			* End of Getting Remaining input
			*******************************************/

		symbol = scanner::scanner (tokenCode, a);
		std::string lastSymbol= "";
		while (/*symbolStack.top().compare("EndSym") != 0*/ !symbolStack.empty()) {
			X = symbolStack.top();
			// std::cout << "\nTop of stack->" << X;
			if (symbolStack.top().compare (lastSymbol) == 0) {
				unsigned i = 0;
				for (auto rhs : T[X]) {
					// std::cout << "\nRHS " << i << ' ' << rhs.first << ' ' << rhs.second;
					if (rhs.second != ERROR_CODE) {
						symbol = rhs.first;
						break;
					}
					++i;
				}
			}
			if (nonterminals.find(X) != nonterminals.end()) {
				if (T[X][symbol] != ERROR_CODE) {
					// Expand nonterminal, replace X with Y1Y2. . .Ym on the stack. Begin with Ym, then Ym-1,..., and Y1 will be on top of the stack.
					// std::cout << "\nTOP->" << symbolStack.top ();
					symbolStack.pop();
					symbolStackV.pop_back ();
					production = T[X][symbol]-1;
					parserAction = "Predict";
					// std::cout << "\nTop of stack->" << X << " Symbol->" << symbol;
					// std::cout<< "\nProduction->" << production;
					for (auto rhsItr = RHSList[production].crbegin(); rhsItr != RHSList[production].crend(); ++rhsItr) {
						if (symbolStack.empty()) {
							lastSymbol =*(RHSList[production].crbegin());
							// std::cout << '\n' << lastSymbol << " Last Symbol\n";
						}

						symbolStack.push (*rhsItr);
						symbolStackV.push_back (*rhsItr);
						// std::cout << "\nGoing on the stack->" << *rhsItr;	
					}
				} else {
					// std::cout << "\nFIRST ERROR\n";
					syntaxError();
				}
			} else {
				// X = symbol
					// std::cout << '\n' << X << ' ' << symbol <<  '\n';
				if (X.compare(symbol) == 0) {
					parserAction = "Match";
					symbolStack.pop();
					symbolStackV.pop_back ();

					if (!symbolStack.empty()) {
						/********************************************
							* Getting Remaining input
							*/
						fileLoc = scanner::infile.tellg ();
						scanner::infile.seekg (0, scanner::infile.end);
						char eof = scanner::infile.peek();
						scanner::infile.seekg (fileLoc);
						// std::cout << "\nPeek of End of File->" << eof;
						std::getline (scanner::infile, remainingInput, eof);

						scanner::infile.seekg (fileLoc);
						scanner::infile.clear();

						// if (remainingInput.size() > 0 && remainingInput[remainingInput.size()-1] != eof && !symbolStack.empty()) {
						// 	remainingInput += eof;
						// }
						if (remainingInput[remainingInput.size()-1]) {
							remainingInput += eof;
						}
					} else {
						remainingInput = "";
					}

					/**
						* End of Getting Remaining input
						*******************************************/

					symbol = scanner::scanner (tokenCode, a);
					// std::cout << "\nSymbol->" << symbol;
				} else {
					// std::cout << "\nSECOND ERROR\n";
					syntaxError();
				}
			}

			std::cout << "\n***********************\n";
			if (parserAction.compare("Match") == 0) {
				std::cout << '\n' << parserAction;
			} else {
				std::cout << '\n' << parserAction << ' ' << production + 1;
			}
			std::cout << "\nRemaining Input:\n" << remainingInput << "\nEnd of Remaining Input"; 
			std::cout << "\nParse Stack -> ";
			for (auto sItr = symbolStackV.crbegin(); sItr != symbolStackV.crend(); ++sItr) {
				std::cout << *sItr << ' ';
			}
			// std::cout << "\n\n";
			std::cout << "\n***********************\n";
		}
	}

	void syntaxError () {
		std::cerr << "\nSyntax Error!\n";
		// exit (1);
	}
};