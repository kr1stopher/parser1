// Rat20F Lexical Analyzer
#include "Lexer.h"
/*

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

*/
// Function handleFileInput to handle input file stream
vector<string> handleFileInput() {
	// declarations
	ifstream inFileStream;
	string filename, line;
	stringstream textStream;
	vector<string> fileLines;

	cout << "Please enter the name of the file to read. (Include .txt)\n";
	cin >> filename;

	// Handle file opening.  
	// Must be a valid file name, or else will constantly ask to repeat
	inFileStream.open(filename);
	if (!inFileStream) {
		cout << "Unable to find file " << filename << "\n";
		while (!inFileStream) {
			cout << "Please enter a valid file. " << endl;
			cin >> filename;
			inFileStream.open(filename);
		}
	}													// While not EOF, process lines into vector of strings
	while (!inFileStream.eof()) {
		getline(inFileStream, line);
		fileLines.push_back(line);
	}
	// Close files
	inFileStream.close();
	return fileLines;

}

// Handle file output
void handleFileOutput(vector<token> tokList) {
	ofstream outFileStream;
	string outFileName;
	cout << "Please enter the name of the file you would like to write out to. (Please add .txt)\n";
	cin >> outFileName;
	// open a ofstream for file name
	outFileStream.open(outFileName);
	cout << "Writing out to file " << outFileName << ".txt";
	// Print out list of tokens using token getter methods
	for (auto iterator = tokList.begin(); iterator != tokList.end(); iterator++) {
		outFileStream << iterator->getLexeme() << "  " << iterator->getTokenType() << endl;
	}
	outFileStream.close();

}

// Function to check keywords and return true if one is found
bool checkKeywords(string input) {
	vector<string> keywords{
	"if", "fi", "else", "while", "for", "return", "get", "double",  "int",
	"long", "string", "signed", "unsigned", "char", "break", "const", "do", "float",
	"sizeof", "void", "class", "struct", "bool", "struct", "enum", "short" };
	for (auto iterator = keywords.begin(); iterator != keywords.end(); iterator++) {
		if (*iterator == input)
			return true;
	}
	return false;
}

// Function to check operators and return true if one is found
bool checkOperators(string input)
{
	string ops[] = { "++", "--", "==", "<=", ">=", "+=", "-=", "*=", "<<", ">>", "::", ":", "*", "+", "-", "=", "/", "<", ">", "=" };
	for (int i = 0; i < sizeof(ops) / sizeof(ops[0]); i++) {
		if (ops[i] == input)
			return true;
	}
	return false;
}

// Function to check separators and return true if one is found
bool checkSeparators(string input)
{
	string seps[] = { "(", ")", "$$", "/*", "*/", ",", ";", "{", "}" };
	for (int i = 0; i < sizeof(seps) / sizeof(seps[0]); i++) {
		if (seps[i] == input)
			return true;
	}
	return false;
}

// Function to add spaces for each case involved in string input
// Helps in process for tokenizer
string addSpaces(string input) {
	// string edit to return the input as an edited string with spaces, if cases and exceptions are found
	string edit = "";
	size_t exceptionLocation = 0;
	bool exceptionVerified = false;
	char cases[] = { '(', ')', ';', ',', '-', '/*', '*/', '+', '-' };
	string exceptions[] = { "++", "--" };


	// Go through special cases, or exceptions, and search if it is present in current string
	for (int i = 0; i < exceptions->length(); i++) {
		if (input.find(exceptions[i]) != std::string::npos) {
			exceptionVerified = true;
			exceptionLocation = input.find(exceptions[i]);
		}
	}

	// for each char in string, determine if it is involved in exceptions or cases
	// if exceptions or special cases are found, add spaces before and after the case/exception
	for (int i = 0; i < input.length(); i++) {
		if (i == (int)exceptionLocation && exceptionVerified) {			//exceptions block
			edit = edit + " " + input[i] + input[i + sizeof(char)] + " ";
			i++;
		}
		else if (input[i] != cases[0] && input[i] != cases[1]				//cases block
			&& input[i] != cases[2] && input[i] != cases[3]
			&& input[i] != cases[4] && input[i] != cases[5]
			&& input[i] != cases[6] && input[i] != cases[7]
			&& input[i] != cases[8])
		{														// if nothing has been found, add char to edit string
			edit = edit + input[i];
		}
		else {													// if cases are found but not exceptions, add spaces
			edit = edit + " " + input[i] + " ";
		}
	}
	return edit;
}


// Lexer function to process a string and return a token of a certain type
token lexer(string lexeme) {

	// Enums to handle final calculation of token type
	enum DFSMTokenTypes { INTEGER, REAL, IDENTIFIER, ERROR };
	DFSMTokenTypes acceptanceStateType = ERROR;
	token currentToken;

	// Initialization of start location for analysis and DFSM Starting State
	currentToken.setLexeme(lexeme);
	char state = 'A';
	char currentCharInLexeme = '\0';
	bool accepted = true;

	// Check if lexeme is an operator or separator
	// if either/or, set tokentype then immediately return;
	if (checkOperators(lexeme)) {
		currentToken.setTokenType("Operator");
		return currentToken;
	}
	if (checkSeparators(lexeme)) {
		currentToken.setTokenType("Separator");
		return currentToken;
	}

	// Check if lexeme is a keyword, if so, immediately return token as such
	if (checkKeywords(lexeme)) {
		currentToken.setTokenType("Keyword");
		return currentToken;
	}

	// Visualization of DFSM 
	// Primarily unused practically
	// Used as visual aid for programming below
	char DFSM[8][4]
	{   // Accepting states:		B, C, D, E, F, H
		// Non-accepting states:  A, G, Z
		// Empty States:		Z
		//__________________________
		//   |  L  | D  | .  | _	   |
		/*A*/{ 'B', 'C', 'Z', 'Z' },
		/*B*/{ 'D', 'E', 'Z', 'F' },
		/*C*/{ 'Z', 'C', 'G', 'Z' },
		/*D*/{ 'D', 'E', 'Z', 'F' },
		/*E*/{ 'D', 'E', 'Z', 'F' },
		/*F*/{ 'D', 'E', 'Z', 'F' },
		/*G*/{ 'Z', 'H', 'Z', 'Z' },
		/*H*/{ 'Z', 'H', 'Z', 'Z' }
	};

	// for each char, determine current state
	for (int i = 0; i < lexeme.size(); i++) {
		currentCharInLexeme = lexeme.at(i);

		// If state is A - Starting State					// The following states maintain the same structure
		if (state == 'A') {
			// If L /Letter							// Comments for State A will be the same for other states except Z
			if (isalpha(currentCharInLexeme)) {
				state = 'B';
				acceptanceStateType = IDENTIFIER;
				accepted = true;
			}// If D/number
			else if (isdigit(currentCharInLexeme)) {
				state = 'C';
				acceptanceStateType = INTEGER;
				accepted = true;
			}// If . 
			else if (currentCharInLexeme == '.') {
				state = 'Z'; //Z
				accepted = false;
			}// If _
			else if (currentCharInLexeme == '_') {
				state = 'Z'; //Z
				accepted = false;
			}
			else state = 'Z';
		}
		else if (state == 'B') {
			acceptanceStateType = IDENTIFIER;		// If DFSM reaches state B, token type will be INTEGER

			if (isalpha(currentCharInLexeme)) {
				state = 'D';
				accepted = true;
			}
			else if (isdigit(currentCharInLexeme)) {
				state = 'E';
				accepted = true;
			}
			else if (currentCharInLexeme == '.') {
				state = 'Z';
				accepted = false;
			}
			else if (currentCharInLexeme == '_') {
				state = 'F'; //Z
				accepted = true;
			}
			else state = 'Z';
		}
		else if (state == 'C') {					// If DFSM reaches state C, token type will be INTEGER
			acceptanceStateType = INTEGER;

			if (isalpha(currentCharInLexeme)) {
				state = 'Z'; //Z
				accepted = false;
			}
			else if (isdigit(currentCharInLexeme)) {
				state = 'C';
				acceptanceStateType = INTEGER;
				accepted = true;
			}
			else if (currentCharInLexeme == '.') {
				state = 'G';
				accepted = false;
			}
			else if (currentCharInLexeme == '_') {
				state = 'Z';
				accepted = false;
			}
			else state = 'Z';
		}
		else if (state == 'D') {
			if (isalpha(currentCharInLexeme)) {
				state = 'D';
				accepted = true;
			}
			else if (isdigit(currentCharInLexeme)) {
				state = 'E';
				accepted = true;
			}
			else if (currentCharInLexeme == '.') {
				state = 'Z';
				accepted = false;
			}
			else if (currentCharInLexeme == '_') {
				state = 'F';
				accepted = true;
			}
			else state = 'Z';
		}
		else if (state == 'E') {
			if (isalpha(currentCharInLexeme)) {
				state = 'D';
				accepted = true;
			}
			else if (isdigit(currentCharInLexeme)) {
				state = 'E';
				accepted = true;
			}
			else if (currentCharInLexeme == '.') {
				state = 'Z';
				accepted = false;
			}
			else if (currentCharInLexeme == '_') {
				state = 'F';
				accepted = true;
			}
			else state = 'Z';
		}
		else if (state == 'F') {
			if (isalpha(currentCharInLexeme)) {
				state = 'D';
				accepted = true;
			}
			else if (isdigit(currentCharInLexeme)) {
				state = 'E';
				accepted = true;
			}
			else if (currentCharInLexeme == '.') {
				state = 'Z';
				accepted = false;
			}
			else if (currentCharInLexeme == '_') {
				state = 'F';
				accepted = true;
			}
			else state = 'Z';
		}
		else if (state == 'G') {
			if (isalpha(currentCharInLexeme)) {
				state = 'Z';
				accepted = false;
			}
			else if (isdigit(currentCharInLexeme)) {
				state = 'H';
				acceptanceStateType = REAL;
				accepted = true;
			}
			else if (currentCharInLexeme == '.') {
				state = 'Z';
				accepted = false;
			}
			else if (currentCharInLexeme == '_') {
				state = 'Z';
				accepted = false;
			}
			else state = 'Z';
		}
		else if (state == 'H') {
			acceptanceStateType = REAL;				// Should DFSM reach state H, token type will be a REAL

			if (isalpha(currentCharInLexeme)) {
				state = 'Z';
				accepted = false;
			}
			else if (isdigit(currentCharInLexeme)) {
				state = 'H';
				acceptanceStateType = REAL;
				accepted = true;
			}
			else if (currentCharInLexeme == '.') {
				state = 'Z';
				accepted = false;
			}
			else if (currentCharInLexeme == '_') {
				state = 'Z';
				accepted = false;
			}
			else state = 'Z';;
		}
		else if (state == 'Z') {						//Empty states, will not be accepted as valid
			accepted = false;
		}
	}

	// Based on Enumerators and whether a certain state was reached
	// Initialize token to be returned as the following
	switch (acceptanceStateType) {
	case INTEGER:
		currentToken.setTokenType("Integer");
		break;
	case REAL:
		currentToken.setTokenType("Real");
		break;
	case IDENTIFIER:
		currentToken.setTokenType("Identifier");
		break;
	default:
		currentToken.setTokenType("ERROR");
		break;
	};


	// Based on final state, accept will be true or false
	// Acceptance will return current Token as is conceived
	// False or default will declare type as invalid
	switch (accepted)
	{
	case true:
		return currentToken;
		break;
	case false:
		currentToken.setTokenType("Invalid - False");
		return currentToken;
		break;
	default:
		currentToken.setTokenType("Invalid - Default");
		return currentToken;
		break;
	};

}

// Tokenizer Helper Function
// Use C strtok_s and strcpy_s to parse vector of strings by " "
vector<string> tokenizer(vector<string> str) {

	vector<string> output;

	for (int i = 0; i < str.size() - 1; i++) {
		char* cstr = (char*)malloc(1000);			// Allocate memory of 1000 for cstr
		char* context = NULL;
		strcpy_s(cstr, 1000, str[i].c_str());

		char* tok = strtok_s(cstr, " ", &context);	// Tokenize through parsing with delimeter " "
		while (tok != 0) {
			output.push_back(tok);
			tok = strtok_s(NULL, " ", &context);
		}
		free(cstr);						// Free memory of cstr
	}

	return output;

}

