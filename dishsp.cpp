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
#include <iomanip>
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

			*out<<"oksoftware HSP 3.2 AX Dumper"<<endl
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

			*out<<"Dump of file "<<argv[1]<<endl<<endl;

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
			using namespace std;

			*out<<"AX FILE HEADER"<<endl;
			*out<< hex << right <<
				"\t" << setw(8) << *((unsigned int *)header->magic) << " Magic Code 'HSP3'" << endl <<
				"\t" << setw(8) << header->version << " Version Number Info" << endl <<
				"\t" << setw(8) << header->maxVal << " Max Count of VAL Object" << endl <<
				"\t" << setw(8) << header->size << " Total File Size" << endl <<

				"\t" << setw(8) << header->pCS << " Ptr to Code Segment" << endl <<
				"\t" << setw(8) << header->maxCS << " Size of Code Segment" << endl <<
				"\t" << setw(8) << header->pDS << " Ptr to Data Segment" << endl <<
				"\t" << setw(8) << header->maxDS << " Size of Data Segment" << endl <<

				"\t" << setw(8) << header->pOT << " Ptr to Object Temp" << endl <<
				"\t" << setw(8) << header->maxOT << " Size of Object Temp" << endl <<
				"\t" << setw(8) << header->pDINFO << " Ptr to Debug Info" << endl <<
				"\t" << setw(8) << header->maxDINFO << " Size of Debug Info" << endl <<

				"\t" << setw(8) << header->pLINFO << " Ptr to LibInfo" << endl <<
				"\t" << setw(8) << header->maxLINFO << " Size of LibInfo" << endl <<
				"\t" << setw(8) << header->pFINFO << " Ptr to FuncInfo" << endl <<
				"\t" << setw(8) << header->maxFINFO << " Size of FuncInfo" << endl <<

				"\t" << setw(8) << header->pMINFO << " Ptr to ModInfo" << endl <<
				"\t" << setw(8) << header->maxMINFO << " Size of ModInfo" << endl <<
				"\t" << setw(8) << header->pFINFO2 << " Ptr to FuncInfo2" << endl <<
				"\t" << setw(8) << header->maxFINFO2 << " Size of FuncInfo2" << endl <<

				"\t" << setw(8) << header->pHPIDAT << " Ptr to HPIDAT" << endl <<
				"\t" << setw(8) << header->maxHPIDAT << " Size of HPIDAT" << endl <<
				"\t" << setw(8) << header->maxVARHPI << " Num of Vartype Plugins" << endl <<
				"\t" << setw(8) << header->bootOption << " Bootup Options" << endl <<
				"\t" << setw(8) << header->runtime << " Ptr to Runtime Name" << endl;
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
