/*
 * Yet Another HSP Compiler
 *
 * dishsp.h : Header of HSP IR Code Disassembler
 *
 * Last modified: 2010/02/10
 *
 * Copyright (C) 2010 oksoftware. All rights reserved.
 *
 */

#include <string>
#include <fstream>
#include "AXLexer.h"

class Dishsp {
	private:
		std::ostream *out;
		std::istream *in;
	public:
		Dishsp(std::ostream *out, int mode);
		void setInput(std::istream *in);
		void write();
		static const int MODE_AXIR = 0;
		static const int MODE_SCRIPT = 1;
	private:
		void writeHeader(AXHeader *header);
		void writeIRs(AXFile *axfile);
		void writeLINFOs(AXFile *axfile);
		void writeSTRUCTDATs(AXFile *axfile);
		void writeSTRUCTPRMs(AXFile *axfile);
		void writeHPIDATs(AXFile *axfile);
		const AXCmdInfo *findCmdById(unsigned short type, unsigned int id);
		std::string paddingString(std::string src, unsigned int size);
};
