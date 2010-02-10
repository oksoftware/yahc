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

#include <fstream>
#include "AXLexer.h"

class Dishsp {
	private:
		std::ostream *out;
		std::istream *in;
	public:
		Dishsp(std::ostream *out);
		void setInput(std::istream *in);
		void write();
	private:
		void writeHeader(AXHeader *header);
};
