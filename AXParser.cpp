/*
 * Yet Another HSP Compiler
 *
 * AXParser.cpp : HSP IR Code Parser
 *
 * Last modified: 2010/02/21
 *
 * Copyright (C) 2010 oksoftware. All rights reserved.
 *
 */

#include <iostream>
#include "AXParser.h"

AXParser::AXParser(AXFile *axfile){
	this->axfile = axfile;
	this->err = &std::cerr;
	return;
}

void AXParser::setErrorOutput(std::ostream *err){
	this->err = err;
	return;
}
void AXParser::parse(){
	this->code = readStatements(axfile);

	return;
}


std::vector<AXStatement> AXParser::readStatements(AXFile *axfile){
	using namespace std;
	vector<AXStatement> code;
	vector<AXIR> IRCode;

	IRCode = axfile->code;
	while(IRCode.size()){
		vector<AXIR> cur = getNextIRLine(&IRCode);
	}
	return code;
}

std::vector<AXIR> AXParser::getNextIRLine(std::vector<AXIR> *IRCode){
	using namespace std;
	bool isFirst = true;
	vector<AXIR> line;
	for(vector<AXIR>::iterator i = IRCode->begin(); i != IRCode->end();){
		if((*i).isTop){
			if(!isFirst){
				break;
			}else{
				isFirst = false;
			}
		}

		line.push_back(*i);
		IRCode->erase(i);
	}
	return line;
}
AXStmtType AXParser::detectStmtType(std::vector<AXIR> *src){
	if(src->size() == 1){
		return COMMAND;
	}else if((src->size() > 1) && (src->at(1).type == TYPE_VAR)){
		return ASSIGNMENT;
	}

	return COMMAND;
}

AXStatement AXParser::readStatement(std::vector<AXIR> src){
	AXStatement ret;
	ret.type = detectStmtType(&src);
	
	if(ret.type == COMMAND){
		ret.cmd = readCommand(&src);
	}else if(ret.type == ASSIGNMENT){
		ret.assign = readAssignment(&src);
	}
	return ret;
}

AXCommand *AXParser::readCommand(std::vector<AXIR> *src){
	AXCommand *dst = new AXCommand;
	return dst;
}

AXAssignment *AXParser::readAssignment(std::vector<AXIR> *src){
	AXAssignment *dst = new AXAssignment;
	return dst;
}
