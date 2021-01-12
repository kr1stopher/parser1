#include "Parser.h"


static bool debug;
static vector<token> tokens;
static int current = 0;

void Parse(vector<token> tokenList, bool debugflag) {
	tokens = tokenList;
	debug = debugflag;
	current = 0;
	Rat20F();
}

bool match(string s) {
	if
		(current >= tokens.size()) {
		error("End of file.");
		exit(1);
		return false;
	}
	if (tokens[current].getLexeme() == s) {
		cout << "Token: " << tokens[current].getTokenType() << "\tLexeme:" << tokens[current].getLexeme() << endl;
		current++;
		//cout << "`------Matched:" << s << endl;
		return true;
	}
	else if ((s == "Identifier" || s == "identifier") && tokens[current].getTokenType() == "Identifier") {
		cout << "Token: " << tokens[current].getTokenType() << "\tLexeme:" << tokens[current].getLexeme() << endl;
		current++;
		return true;
	}
	else if (s == "int" && tokens[current].getTokenType() == "Integer") {
		cout << "Token: " << tokens[current].getTokenType() << "\tLexeme:" << tokens[current].getLexeme() << endl;
		current++;
		return true;
	}
	else if (s == "real" && tokens[current].getTokenType() == "Real") {
		cout << "Token: " << tokens[current].getTokenType() << "\tLexeme:" << tokens[current].getLexeme() << endl;
		current++;
		return true;
	}
	else if (s == "bool" && tokens[current].getTokenType() == "Boolean") {
		cout << "Token: " << tokens[current].getTokenType() << "\tLexeme:" << tokens[current].getLexeme() << endl;
		current++;
		return true;
	}
	else {
		cout << "ERROR: expected: " << tokens[current].getLexeme() << " found: " << s << endl;
		exit(1);
		//current++;
		return false;
	}
}

bool lookahead(string s) {

	if (current >= tokens.size()) {
		error("End of file.");
		exit(1);
		return false;
	}
	else if ((s == "Identifier" || s == "identifier") && tokens[current].getTokenType() == "Identifier") {
		//cout << "Token: " << tokens[current].getTokenType() << "\tLexeme:" << tokens[current].getLexeme() << endl;

		return true;

	}
	else if (s == "int" && tokens[current].getTokenType() == "Integer") {
		return true;
	}
	else if (s == "real" && tokens[current].getTokenType() == "Real") {
		return true;
	}
	else if (s == "bool" && tokens[current].getTokenType() == "Boolean") {
		return true;
	}
	//cout << " Lookahead:" << tokens[current].getLexeme() << " looking for: "<<s<< endl;
	if (tokens[current].getLexeme() == s) {
		return true;
	}
	return false;
}

void error(string s) {
	cout << s << endl;
	exit(1);
}

void Rat20F() {
	if (debug) {
		cout << "<Rat20F> ::= <Opt Function Definitions> $$ <Opt Declaration List> <Statement List> $$" << endl;
	}
	optFunDef();
	match("$$");
	//optDecList();
	stmtList();
}

void optFunDef() {
	if (debug) {
		cout << "<Opt Function Definitions> ::= <Function Definitions> | <Empty>" << endl;
	}
	if (lookahead("function")) {
		funDef();
	}
}

void funDef() {
	if (debug) {
		cout << "<Function Definitions> ::= <Function> | <Function> <Function Definitions>" << endl;
	}
	function();
	if (lookahead("function")) {
		funDef();
	}
}

void function() {
	if (debug) {
		cout << "<Function> ::= function <Identifier> ( <Opt Parameter List> ) <Opt Declaration List> <Body>" << endl;
	}
	match("function");
	match("Identifier");
	match("(");
	optParamList();
	match(")");
	optDecList();
	body();
}

void optParamList() {
	if (debug) {
		cout << "<Opt Parameter List> ::= <Parameter List> | <Empty>" << endl;
	}
	if (!lookahead(")")) {
		paramList();
	}
}

void paramList() {
	if (debug) {
		cout << "<Parameter List> ::= <Parameter> | <Parameter> , <Parameter List>" << endl;
	}
	parameter();
	if (lookahead(",")) {
		match(",");
		parameter();
		paramList();
	}
}

void parameter() {
	if (debug) {
		cout << "<Parameter> ::= <IDs> <Qualifier>" << endl;
	}
	ids();
	qualifier();
}

void qualifier() {
	if (debug) {
		cout << "<Qualifier> ::= int | boolean | real" << endl;
	}
	if (lookahead("int"))
		match("int");
	else if (lookahead("bool"))
		match("bool");
	else if (lookahead("real"))
		match("real");
	else {
		error("Error: Expected identifier.");
	}
}

void body() {
	if (debug) {
		cout << "<Body> ::= { < Statement List> }" << endl;
	}
	match("{");
	stmtList();
	match("}");
}



void optDecList() {
	if (debug) {
		cout << "<Opt Declaration List> ::= <Declaration List> | <Empty>" << endl;
	}
	if (lookahead("Integer") || lookahead("Bool") || lookahead("Real")) {
		decList();
	}
}

void decList() {
	if (debug) {
		cout << "<Declaration List> := <Declaration> ; | <Declaration> ; <Declaration List>" << endl;
	}
	declaration();
	match(";");
	if (lookahead("Integer") || lookahead("bool") || lookahead("Real")) {
		decList();
	}
}


void declaration() {
	if (debug) {
		cout << "<Declaration> ::= <Qualifier > <IDs>" << endl;
	}
	qualifier();
	ids();
}

void ids() {
	if (debug) {
		cout << "<IDs> ::= <Identifier> | <Identifier>, <IDs>" << endl;
	}
	match("identifier");
	if (lookahead(",")) {
		match("identifier");
		ids();
	}
}
void stmtList() {
	if (debug) {
		cout << "<Statement List> ::= <Statement> | <Statement> <Statement List>" << endl;
	}
	statement();
	if (!lookahead("}"))
		stmtList();
}

void statement() {
	if (debug) {
		cout << "<Statement> ::= <Compound> | <Assign> | <If> | <Return> | <Print> | <Scan> | <While>" << endl;
	}
	if (lookahead("{"))
		compound();
	else if (lookahead("Identifier"))
		assign();

	else if (lookahead("if"))
		ifFun();

	else if (lookahead("return"))
		returnFun();

	else if (lookahead("put"))
		printFun();

	else if (lookahead("get"))
		scan();

	else if (lookahead("while"))
		whileFun();

}

void compound() {
	if (debug) {
		cout << "<Compound> ::= { <Statement List> }" << endl;
	}
	match("{");
	stmtList();
	match("}");
}

void assign() {

	if (debug) {
		cout << "<Assign> ::= <Identifier> = <Expression> ;" << endl;
	}
	match("identifier");
	match("=");
	expression();
	match(";");

}

void ifFun() {
	if (debug) {
		cout << "<If> ::= if ( <Condition> ) <Statement> fi |if ( <Condition> ) <Statement> else <Statement> fi" << endl;
	}
	match("if");
	match("(");
	condition();
	match(")");
	statement();
	if (lookahead("fi"))
		match("fi");

	else if (lookahead("else")) {
		match("else");
		statement();
		match("fi");
	}
}

void returnFun() {
	if (debug) {
		cout << "<Return> ::= return ; | return <Expression> ;" << endl;
	}
	match("return");
	if (lookahead(";"))
		match(";");

	else {
		expression();
		match(";");
	}
}

void printFun() {
	if (debug) {
		cout << "<Print> ::= put ( <Expression>);" << endl;
	}
	match("put");
	match("(");
	expression();
	match(")");
	match(";");
}
void scan() {
	if (debug) {
		cout << "<Scan> ::= get ( <IDs> );" << endl;
	}
	match("get");
	match("(");
	ids();
	match(")");
	match(";");
}
void whileFun() {
	if (debug) {
		cout << "<While> ::= while ( <Condition> ) <Statement>" << endl;
	}
	match("while");
	match("(");
	condition();
	match(")");
	statement();
}
void condition() {
	if (debug) {
		cout << "<Condition> ::= <Expression> <Relop> <Expression>" << endl;
	}
	expression();
	relop();
	expression();
}
void relop() {
	if (debug) {
		cout << "<Relop> ::= == | != | > | < | <= | =>" << endl;
	}
	if (lookahead("=="))
		match("==");
	else if (lookahead("!="))
		match("!=");
	else if (lookahead(">"))
		match(">");
	else if (lookahead("<"))
		match("<");
	else if (lookahead("=>"))
		match("=>");
	else if (lookahead("<="))
		match("<=");
	else
		error("Relop expected. Missing : == | != | > | < | <= | =>");

}
void expression() {
	if (debug) {
		cout << "<Expression> ::= <Term> <Expression Prime>" << endl;
	}

	term();
	expressionPrime();
}
void expressionPrime() {
	if (debug) {
		cout << "<Expression Prime> ::= +<Expression> | -<Expression> | ε" << endl;
	}
	if (lookahead("+")) {
		match("+");
		expression();
	}
	else if (lookahead("-")) {
		match("-");
		expression();
	}

}
void term() {
	if (debug) {
		cout << "<Term> ::= <Factor><Term Prime>" << endl;
	}
	factor();
	termPrime();
}
void termPrime() {
	if (debug) {
		cout << "<Term Prime> ::= *<Term> | /<Term> | ε" << endl;
	}
	if (lookahead("*")) {
		match("*");
		term();
	}
	else if (lookahead("/")) {
		match("/");
		term();
	}
}
void factor() {
	if (debug) {
		cout << "<Factor> ::= - <Primary> | <Primary>" << endl;
	}
	if (lookahead("-")) {
		match("-");
	}
	primary();
}
void primary() {
	if (debug) {
		cout << "<Primary> ::= <Identifier> | <Integer> | <Identifier> ( <IDs> ) | ( <Expression> ) | <Real> | true | false" << endl;
	}
	if (lookahead("Identifier")) {
		match("Identifier");
		if (lookahead("(")) {
			match("(");
			ids();
			match(")");
		}
	}
	else if (lookahead("int"))
		match("int");

	else if (lookahead("real"))
		match("real");

	else if (lookahead("boolean"))
		match("boolean");

	else if (lookahead("(")) {
		match("(");
		expression();
		match(")");
	}
	else {
		error("Invalid Identifier. ");
	}

}
void empty() {
	if (debug) {
		cout << "<Empty> ::= " << endl;
	}
}
