/*
 * Yet Another HSP Compiler
 *
 * yahc.cpp : Main Source File
 *
 * Last modified: 2010/02/10
 *
 * Copyright (C) oksoftware. All rights reserved.
 *
 */

#include <iostream>
#include <fstream>
#include "dishsp.h"

typedef struct {
	bool dishsp;
	std::string input;
	bool noInput;
} YahcOptions;

static void usage(){
	using namespace std;
	cerr<<"Usage: yahc [options] axfile"<<endl;
	return;
}

int main(int argc, char *argv[]){
	using namespace std;
	YahcOptions opt;
	ifstream axfile;

	opt.dishsp = false;
	opt.noInput = true;

	for(int i = 1; i < argc; i++){
		string cur(argv[i]);
		if(cur == "--dishsp"){
			opt.dishsp = true;
		}else if(cur == "--help"){
			usage();
			return 1;
		}else{
			opt.input = cur;
			opt.noInput = false;
		}
	}

	if(opt.noInput){
		cerr<<"Error: No input file"<<endl;
		usage();
		return 1;
	}

	axfile.open(opt.input.c_str(), ios::in | ios::binary);
	if(axfile.fail()){
		cerr<<"Error: Couldn't open file"<<endl;
		return 1;
	}

	if(opt.dishsp){
		Dishsp dishsp(&cout);
		dishsp.setInput(&axfile);
		dishsp.write();
		return 0;
	}

	AXLexer lexer(&axfile);
	lexer.lex();


	axfile.close();

	return 0;
}
