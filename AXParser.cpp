/*
 * Yet Another HSP Compiler
 *
 * AXParser.cpp : HSP IR Code Parser
 *
 * Last modified: 2010/02/11
 *
 * Copyright (C) 2010 oksoftware. All rights reserved.
 *
 */

#include "AXParser.h"

AXParser::AXParser(AXFile *axfile){
	this->axfile = axfile;
	return;
}

void AXParser::parse(){
	this->code = readStatements(axfile);

	return;
}


std::vector<AXStatement> AXParser::readStatements(AXFile *axfile){
	using namespace std;
	vector<AXStatement> code;

	IRCode = axfile->code;
	return code;
}

std::vector<AXIR> AXParser::getNextIRLine(){
	using namespace std;
	vector<AXIR> line;
	for(vector<AXIR>::iterator i = IRCode.begin(); i != IRCode.end();){
		if((*i).isTop){
			break;
		}

		line.push_back(*i);
		IRCode.erase(i);
	}
	return line;
}
