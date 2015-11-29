/*
	 nicole cranon <nicole.cranon@ucdenver.edu>
	 csci 4640, fall 2015
	 homework 4 - universal scanner
 */

#ifndef _USCANNER
#define _USCANNER

#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>

namespace scanner {
	extern std::vector<std::unordered_map<std::string, int> > T;
	extern std::vector<std::unordered_map<std::string, std::string> > actionTable;
	extern std::unordered_map<int, std::string> terminalState;
	extern std::ifstream infile;
	extern const char *file;

	// actions which the scanner may take
	typedef enum {
		Error,
		MoveAppend,
		MoveNoAppend,
		HaltAppend,
		HaltNoAppend,
		HaltReuse
	} Action;

	// terminal states holder

	extern std::string action_type[];

	void readTransitionTable (const char* const filename, 
		std::vector<std::unordered_map<std::string, int>>& T,
		std::unordered_map<int, std::string>& termState);

	/*
		 lookupCode

		 precondition - 
		 current state, the current char, and token code variable

		 postcondition - 
		 populates the token code variable
	 */
	void lookupCode (int state, char c, int& tokenCode);

	/*
		 checkException

		 precondition - 
		 a proper token code, and the string that contains the token contents

		 postcondition -
		 alters the the token code if there is an exception
	 */
	std::string checkException (int& tokenCode, std::string& tokenText);

	/*
		 read

		 precondition - 
		 a char variable to hold the read in character and an existing file 
		 stream buffer

		 postcondition -
		 populates the char provided with the next character from the file
		 stream and advances the file stream one character
	 */
	void read (char& c);

	/*
		 currentChar

		 precondition - 
		 an existing file stream buffer

		 postcondition -
		 returns the next char from the file stream but does not advance 
		 the input stream
	 */
	char currentChar ();

	/*
		 consumeChar

		 precondition -
		 an existing file stream buffer

		 postcondition -
		 advances the input stream by one character
	 */
	void consumeChar ();

	/*
		 clearBuffer

		 precondition - 
		 a string 

		 postcondition - 
		 sets the given string to the empty string
	 */
	void clearBuffer (std::string& buffer);

	/*
		 lexicalError

		 precondition -
		 a lexical error has occured

		 postcondition -
		 ends porgress of scanner and prints an error message to the std output
	 */
	void lexicalError ();

	/*
		 nextState
		 is the table for moves from state to state. It stores the next 
		 state to visit

		 precondition - 
		 a state variable and the current character

		 postcondition -
		 populates the state variable given with the next state to enter
	 */
	void nextState (int& state, char c);

	/*
		 action

		 precondition -
		 the current state, and the current character

		 postcondition -
		 returns the next action for the scanner to take
	 */
	Action action (int state, char c);

	void readActionTable (const char* const actionTableFile);

	/*
		 scanner

		 precondition -
		 an existing file read stream, a variable for the token code, and
		 a string variable to hold the token text

		 postcondtion -
		 populates the token code, and token text variables with the read
		 token's code and its text
	 */
	std::string scanner (int& tokenCode, std::string& tokenText);

	std::string getSymbol (const int& tokenCode, const std::string& tokenText);



}

#endif
