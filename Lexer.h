#ifndef _LEXER
#define _LEXER

// Included Libraries
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string.h>

using namespace std;

// Definition for class Token

class token {
private:
	string lexeme = "Null", tokenType = "Null";
public:

	// setter methods
	void setLexeme(string lex) {
		lexeme = lex;
	}
	void setTokenType(string tok) {
		tokenType = tok;
	}

	// getter methods
	string getLexeme() {
		return lexeme;
	}
	string getTokenType() {
		return tokenType;
	}


	// print token Method
	void printToken() {
		cout << "lexeme: " << lexeme << "\t\tToken Type: " << tokenType << "\n";
	}

};

vector<string> handleFileInput();
void handleFileOutput(vector<token> tokList);
bool checkKeywords(string input);
bool checkOperators(string input);
bool checkSeparators(string input);
string addSpaces(string input);
token lexer(string lexeme);
vector<string> tokenizer(vector<string> str);
vector<string> removeComments(vector<string> str);

#endif