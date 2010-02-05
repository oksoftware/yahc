/*
 * Yet Another HSP Compiler
 *
 * yahc.cpp : Main Source File
 *
 * Last modified: 2010/02/04
 *
 * Copyright (C) oksoftware. All rights reserved.
 *
 */

#include <iostream>
#include <fstream>
#include "AXLexer.h"

int main(int argc, char *argv[]){
	using namespace std;
	ifstream axfile;

	if(argc < 2){
		cout<<"Error: No input file"<<endl;
		return 1;
	}

	axfile.open(argv[1], ios::in | ios::binary);
	if(axfile.fail()){
		cout<<"Error: Couldn't open file"<<endl;
		return 1;
	}

	AXLexer lexer(&axfile);
	lexer.lex();


	axfile.close();

	return 0;
}
