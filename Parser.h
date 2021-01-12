
#ifndef _PARSER
#define _PARSER

// Included Libraries
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include "Lexer.h"

using namespace std;

void Parse(vector<token> tokenList, bool debugflag);
void Rat20F();
void optFunDef();
void funDef();
void function();
void optParamList();
void paramList();
void parameter();
void qualifier();
void body();
void stmtList();
void optDecList();
void decList();
void declaration();
void ids();
void statement();
void compound();
void assign();
void ifFun();
void returnFun();
void printFun();
void scan();
void whileFun();
void condition();
void relop();
void expression();
void expressionPrime();
void term();
void termPrime();
void factor();
void primary();
void empty();
void error(string s);

#endif