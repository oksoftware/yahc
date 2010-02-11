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

class AXParser {
	private:
		int pos;
		std::vector<AXStatement *> *statement;
		std::vector<int> label;
	public:
		AXParser(AXFile *axfile);
	private:
		std::vector<AXStatement *> *readStatements();
		AXStatement *readStatement();
};
