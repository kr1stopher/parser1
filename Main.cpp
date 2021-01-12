// Included Libraries
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include "Lexer.h"
#include "Parser.h"

using namespace std;


// Main Program
int main() {

	// Boolean to continue running program unless false
	bool alive = true;

	// Do-While Loop for program
	do {

		// Vector String Containers for entire program
		vector<string> inputContainer = handleFileInput();			// Processing for file input
		vector<string> inputContainerEdit1;						// Edit 1 for adding spaces for specific cases to create concise tokenization
		vector<string> inputContainerEdit2;						// Edit 2 for processing through tokenizer() 

		// Vector  tokenlist
		vector<token> tokenList;									// Vector of Tokens, to process with lexer and add into vector


		char answer = 'x';										// UI interaction inputs with char input
		bool printOutBool = false;								// Bool to handle errors in user input


		// Grab all lines of text and place them into vector string inputContainer
		for (auto iterator = inputContainer.begin(); iterator != inputContainer.end(); iterator++) {
			//while adding each line, edit each line with addSpaces()
			inputContainerEdit1.push_back(addSpaces(*iterator));
		}

		// Separate each string by delimeter " "
		inputContainerEdit2 = tokenizer(inputContainerEdit1);

		// for each string in Edit2, process through lexer.
		// Then output a token, and add to tokenList vector
		for (auto iterator = inputContainerEdit2.begin(); iterator != inputContainerEdit2.end(); iterator++) {
			tokenList.push_back(lexer(*iterator));
		}

		// print out token information 
		for (auto iterator = tokenList.begin(); iterator != tokenList.end(); iterator++) {
			iterator->printToken();
		}


		Parse(tokenList, true);



		// Block to handle user input for printing out text file
		cout << "Would you like to print these out to a text file?  Y/N\n";
		while (printOutBool == false) {
			cin >> answer;
			switch (answer) {
			case 'y':
			case'Y':
				handleFileOutput(tokenList);
				printOutBool = true;
				break;
			case 'n':
			case 'N':
				cout << "Have a good day.\n";
				printOutBool = true;
				break;
			default:
				cout << "Please enter a valid answer.\n";
				break;
			}

		}

		// Block to handle user input for  Exit or Repeat of Program
		cout << "\nExit Program or Repeat Program? \nY for Exit \nN for Repeat. \nY/N\n";
		printOutBool = false;

		while (printOutBool == false) {
			cin >> answer;
			switch (answer) {
			case 'y':
			case'Y':
				alive = false;
				printOutBool = true;
				break;
			case 'n':
			case 'N':
				//continue;
				printOutBool = true;
				break;
			default:
				cout << "Please enter a valid answer.\n";
				printOutBool = false;
				break;
			}

		}

	} while (alive);
	return 0;
}