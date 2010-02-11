/*
 * Yet Another HSP Compiler
 *
 * dishsp.cpp : HSP IR Code Disassembler
 *
 * Last modified: 2010/02/10
 *
 * Copyright (C) 2010 oksoftware. All rights reserved.
 *
 */

#include <iostream>
#include <iomanip>
#include <sstream>
#include "dishsp.h"

Dishsp::Dishsp(std::ostream *out){
	using namespace std;
	this->out = out;

	*out<<"oksoftware HSP 3.2 AX Dumper"<<endl
	    <<"Copyright(C) 2010 oksoftware. All rights reserved."<<endl<<endl;
	return;
}

void Dishsp::setInput(std::istream *in){
	this->in = in;
	return;
}

void Dishsp::write(){
	AXLexer *lexer = new AXLexer(in);
	lexer->lex();

	writeHeader(lexer->header);
	writeIRs(lexer);

	delete lexer;
	return;
}

void Dishsp::writeHeader(AXHeader *header){
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
		"\t" << setw(8) << header->runtime << " Ptr to Runtime Name" << endl << endl;
	return;
}

void Dishsp::writeIRs(AXFile *axfile){
	using namespace std;
	int cnt = 0;

	*out<<"AX IR CODE"<<endl<<endl;

	for(vector<AXIR *>::iterator i = axfile->code->begin(); i != axfile->code->end(); i++){
		*out<<hex<<right<<setw(8)<<cnt<<":"
		    <<setw(8)<<(*i)->type;
		*out<<endl;
		cnt++;
	}
	
	return;
}

std::vector<std::string> Dishsp::splitString(std::string haystack, std::string needle){
	using namespace std;
	vector<string> ret;
	for(int i = 0, n; i <= haystack.length(); i = n + 1){
		n = haystack.find_first_of(needle, i);
		if(n == string::npos) n = haystack.length();
		ret.push_back(haystack.substr(i, n - i));
	}
	return ret;
}

std::string Dishsp::stoi(std::string src){
	using namespace std;
	istringstream iss(src);
	string ret;
	iss>> std::hex >> ret;
	return ret;
}
