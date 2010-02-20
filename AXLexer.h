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

typedef struct {
	unsigned int jumpto, bytes;
} JumpToQueue;

class AXLexer : public AXFile {
	private:
		std::istream *src;
		std::vector<JumpToQueue> jumpToQueue;
		std::vector<int> rawLabel;
	public:
		AXLexer(std::istream *src);
		void lex();
	private:
		int getInt();
		short getShort();
		unsigned int getUnsignedInt();
		unsigned short getUnsignedShort();
		char getChar();
		AXHeader getHeader();
		AXIR getIR(unsigned int index, int *len);
		std::vector<AXIR> getIRList();
		unsigned char *getDataSegment();
		std::vector<int> getObjectTemp();
		std::vector<unsigned char> getDINFO();
		AXLibDat getLIBDAT();
		std::vector<AXLibDat> getLIBDATList();
		AXStructDat getSTRUCTDAT();
		std::vector<AXStructDat> getSTRUCTDATList();
		AXStructPrm getSTRUCTPRM();
		std::vector<AXStructPrm> getSTRUCTPRMList();
		AXHpiDat getHPIDAT();
		std::vector<AXHpiDat> getHPIDATList();
		
};
