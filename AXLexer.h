/*
 * Yet Another HSP Compiler
 *
 * AXLexer.h : Header of AX IR Code Lexer
 *
 * Last modified: 2010/02/04
 *
 * Copyright (C) oksoftware. All rights reserved.
 *
 */
#include <istream>
#include <vector>
#include "AXStruct.h"

class AXLexer {
	private:
		std::istream *src;
	public:
		AXHeader *header;
		std::vector<AXIR *> *code;
		unsigned char *data;
		std::vector<int> *label;
		std::vector<unsigned char> *debug;
		std::vector<AXLibDat *> *libDat;
		std::vector<AXStructDat *> *structDat;
		std::vector<AXStructPrm *> *structPrm;
		std::vector<AXHpiDat *> *hpiDat;

	public:
		AXLexer(std::istream *src);
		void lex();
	private:
		int getInt();
		short getShort();
		char getChar();
		template <class T> std::vector<T> *getList(std::istream *src, T (*func)(), int begin, int length);
		AXHeader *getHeader();
		AXIR *getIR();
		std::vector<AXIR *> *getIRList();
		unsigned char *getDataSegment();
		std::vector<int> *getObjectTemp();
		std::vector<unsigned char> *getDINFO();
		AXLibDat *getLIBDAT();
		std::vector<AXLibDat *> *getLIBDATList();
		AXStructDat *getSTRUCTDAT();
		std::vector<AXStructDat *> *getSTRUCTDATList();
		AXStructPrm *getSTRUCTPRM();
		std::vector<AXStructPrm *> *getSTRUCTPRMList();
		AXHpiDat *getHPIDAT();
		std::vector<AXHpiDat *> *getHPIDATList();
};
