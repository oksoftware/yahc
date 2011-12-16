/*
 * Yet Another HSP Compiler
 *
 * AXLexer.cpp : AX IR Code Lexer
 *
 * Last modified: 2010/02/06
 *
 * Copyright (C) 2010 oksoftware. All rights reserved.
 *
 */

#include "AXLexer.h"
#include <iostream>

AXLexer::AXLexer(std::istream *src){
	this->src = src;

	return;
}

void AXLexer::lex(){
	this->header = getHeader();

	/* Read raw label first*/
	this->rawLabel = getObjectTemp();

	this->code = getIRList();
	this->data = getDataSegment();
	this->debug = getDINFO();
	this->libDat = getLIBDATList();
	this->structDat = getSTRUCTDATList();
	this->structPrm = getSTRUCTPRMList();
	this->hpiDat = getHPIDATList();

	return;
}
int AXLexer::getInt(){
	int tmp = 0;
	src->read((char *)&tmp, sizeof(tmp));
	return tmp;
}

short AXLexer::getShort(){
	short tmp;
	src->read((char *)&tmp, sizeof(tmp));
	return tmp;
}

unsigned int AXLexer::getUnsignedInt(){
	unsigned int tmp = 0;
	src->read((char *)&tmp, sizeof(tmp));
	return tmp;
}

unsigned short AXLexer::getUnsignedShort(){
	unsigned short tmp;
	src->read((char *)&tmp, sizeof(tmp));
	return tmp;
}

char AXLexer::getChar(){
	char tmp;
	src->read((char *)&tmp, sizeof(tmp));
	return tmp;
}

AXHeader AXLexer::getHeader(){
	AXHeader header;

	src->read(header.magic, 4);
	header.version = getInt();
	header.maxVal = getInt();
	header.size = getInt();

	header.pCS = getInt();
	header.maxCS = getInt();
	header.pDS = getInt();
	header.maxDS = getInt();

	header.pOT = getInt();
	header.maxOT = getInt();
	header.pDINFO = getInt();
	header.maxDINFO = getInt();

	header.pLINFO = getInt();
	header.maxLINFO = getInt();
	header.pFINFO = getInt();
	header.maxFINFO = getInt();

	header.pMINFO = getInt();
	header.maxMINFO = getInt();
	header.pFINFO2 = getInt();
	header.maxFINFO2 = getInt();

	header.pHPIDAT = getInt();
	header.maxHPIDAT = getShort();
	header.maxVARHPI = getShort();
	header.bootOption = getInt();
	header.runtime = getInt();

	return header;
}

AXIR AXLexer::getIR(unsigned int index, int *len){
	AXIR ir;
	unsigned short typeWord = 0;
	bool isLong = 0;

	typeWord = getUnsignedShort();
	ir.type   = typeWord & 0x1FFF;/* CSTYPE */
	ir.isTop  = typeWord & 0x2000;/* EXFLG_1 */
	ir.isSepr = typeWord & 0x4000;/* EXFLG_2 */
	isLong     = typeWord & 0x8000;/* If the IR code of these bytes is Long */

	if(isLong){
		ir.code = getUnsignedInt();
		*len = *len + 6;
	}else{
		ir.code = getUnsignedShort();
		*len = *len + 4;
	}

	/* TYPE_CMPCMD has an address which is for jumping to else or its end */
	if(ir.type == TYPE_CMPCMD){
		JumpToQueue rewriter;

		*len = *len + 2;

		rewriter.jumpto = index;
		ir.jump = 0;
		rewriter.bytes = getUnsignedShort() * 2 + *len;

		jumpToQueue.push_back(rewriter);
	}
	return ir;
}

std::vector<AXIR> AXLexer::getIRList(){
	int cur = 0;

	std::vector<AXIR> list;

	src->seekg(header.pCS, std::ios::beg);

	while(cur < header.maxCS){
		int len = 0;
		/* Code Position */
		codePos.push_back(cur);

		/* Get IR */
		list.push_back(getIR(list.size(), &len));
		cur += len;
		/* JumpTo Queue */
		for(std::vector<JumpToQueue>::iterator i = jumpToQueue.begin(); i != jumpToQueue.end();){
			(*i).bytes -= len;
			if((*i).bytes <= 0){
				list.at((*i).jumpto).jump = list.size();
				jumpToQueue.erase(i);
				continue;
			}
			i++;
		}
		/* Label Queue */
		for(std::vector<int>::iterator i = rawLabel.begin(); i != rawLabel.end();){
			if(*i == (cur - len)){
				label.push_back(list.size() - 1);
				rawLabel.erase(i);
				continue;
			}
			i++;
		}

	}

	return list;
}

unsigned char *AXLexer::getDataSegment(){
	unsigned char *ds = new unsigned char[header.maxDS];

	src->seekg(header.pDS, std::ios::beg);

	src->read((char *)ds, header.maxDS);

	return ds;
}

std::vector<int> AXLexer::getObjectTemp(){
	std::vector<int> list(header.maxOT / sizeof(int));

	src->seekg(header.pOT, std::ios::beg);

	for(std::vector<int>::iterator i = list.begin(); i != list.end(); i++){
		*i = getInt() * 2;
	}

	return list;
}

std::vector<unsigned char> AXLexer::getDINFO(){
	std::vector<unsigned char> dinfo(header.maxDINFO);

	src->seekg(header.pDINFO, std::ios::beg);

	for(std::vector<unsigned char>::iterator i = dinfo.begin(); i != dinfo.end(); i++){
		*i = (unsigned char)getChar();
	}

	return dinfo;
}

AXLibDat AXLexer::getLIBDAT(){
	AXLibDat libDat;

	libDat.flag = getInt();
	libDat.nameIndex = getInt();
	libDat.hLib = (void *)getInt();
	libDat.clsid = getInt();

	return libDat;
}

std::vector<AXLibDat> AXLexer::getLIBDATList(){
	std::vector<AXLibDat> list;

	src->seekg(header.pLINFO, std::ios::beg);

	while(src->tellg() < (header.pLINFO + header.maxLINFO)){
		list.push_back(getLIBDAT());
	}

	return list;
}


AXStructDat AXLexer::getSTRUCTDAT(){
	AXStructDat structDat;

	structDat.index = getShort();
	structDat.subId = getShort();
	structDat.prmIndex = getInt();
	structDat.prmMax = getInt();
	structDat.nameIndex = getInt();
	structDat.size = getInt();
	structDat.OTIndex = getInt();
	structDat.proc = (void *)getInt();
	return structDat;
}

std::vector<AXStructDat> AXLexer::getSTRUCTDATList(){
	std::vector<AXStructDat> list;

	src->seekg(header.pFINFO, std::ios::beg);

	while(src->tellg() < (header.pFINFO + header.maxFINFO)){
		list.push_back(getSTRUCTDAT());
	}

	return list;
}

AXStructPrm AXLexer::getSTRUCTPRM(){
	AXStructPrm structPrm;

	structPrm.mpType = getShort();
	structPrm.subId = getShort();
	structPrm.offset = getInt();

	return structPrm;
}

std::vector<AXStructPrm> AXLexer::getSTRUCTPRMList(){
	std::vector<AXStructPrm> list;

	src->seekg(header.pMINFO, std::ios::beg);

	while(src->tellg() < (header.pMINFO + header.maxMINFO)){
		list.push_back(getSTRUCTPRM());
	}

	return list;
}

AXHpiDat AXLexer::getHPIDAT(){
	AXHpiDat hpiDat;

	hpiDat.flag = getShort();
	hpiDat.option = getShort();
	hpiDat.libName = getInt();
	hpiDat.funcName = getInt();
	hpiDat.libPtr = (void *)getInt();

	return hpiDat;
}

std::vector<AXHpiDat> AXLexer::getHPIDATList(){
	std::vector<AXHpiDat> list;

	src->seekg(header.pHPIDAT, std::ios::beg);

	while(src->tellg() < (header.pHPIDAT + header.maxHPIDAT)){
		list.push_back(getHPIDAT());
	}

	return list;
}


