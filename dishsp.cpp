/*
 * Yet Another HSP Compiler
 *
 * dishsp.cpp : HSP IR Code Disassembler
 *
 * Last modified: 2010/02/06
 *
 * Copyright (C) 2010 oksoftware. All rights reserved.
 *
 */

#include <iostream>
#include <fstream>
#include "AXLexer.h"

class Dishsp {
	private:
		std::ostream *out;
		std::istream *in;

	public:
		Dishsp(std::ostream *out){
			using namespace std;
			this->out = out;

			*out<<"oksoftware HSP 3.2 IR Code Disassembler"<<endl
			    <<"Copyright(C) 2010 oksoftware. All rights reserved."<<endl<<endl;
			return;
		}
		void setInput(std::istream *in){
			this->in = in;
			return;
		}

		int parseArgv(int argc, char *argv[]){
			using namespace std;

			if(argc < 2){
				cerr<<"No input file."<<endl;
				return 1;
			}

			in = new ifstream(argv[1], ios::in | ios::binary);

			if(in->fail()){
				cerr<<"Couldn't open the file."<<endl;
				return 1;
			}
			return 0;
		}

		void write(){
			AXLexer *lexer = new AXLexer(in);
			lexer->lex();

			writeHeader(lexer->header);

			delete lexer;
			return;
		}

		void writeHeader(AXHeader *header){
			/**/
			return;
		}
};
int main(int argc, char *argv[]){
	Dishsp *dishsp = new Dishsp(&std::cout);

	if(dishsp->parseArgv(argc, argv)){
		return 1;
	}

	dishsp->write();

	delete dishsp;
	return 0;
}
