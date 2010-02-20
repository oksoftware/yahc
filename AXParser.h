/*
 * Yet Another HSP Compiler
 *
 * AXParser.h : Header of HSP IR Code Parser
 *
 * Last modified: 2010/02/11
 *
 * Copyright (C) 2010 oksoftware. All rights reserved.
 *
 */

#include <vector>
#include "AXStruct.h"

class AXParser : public AXTree {
	private:
		AXFile *axfile;
		std::vector<AXIR> IRCode;
	public:
		AXParser(AXFile *axfile);
		void parse();
	private:
		std::vector<AXStatement> readStatements(AXFile *axfile);
		AXStatement readStatement();
		std::vector<AXIR> getNextIRLine();
};
