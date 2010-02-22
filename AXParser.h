/*
 * Yet Another HSP Compiler
 *
 * AXParser.h : Header of HSP IR Code Parser
 *
 * Last modified: 2010/02/21
 *
 * Copyright (C) 2010 oksoftware. All rights reserved.
 *
 */

#include <vector>
#include "AXStruct.h"

class AXParser : public AXTree {
	private:
		std::ostream *err;
		AXFile *axfile;
	public:
		AXParser(AXFile *axfile);
		void setErrorOutput(std::ostream *err);
		void parse();
	private:
		std::vector<AXStatement> readStatements(AXFile *axfile);
		AXStmtType detectStmtType(std::vector<AXIR> *src);
		AXStatement readStatement(std::vector<AXIR> src);
		AXCommand *readCommand(std::vector<AXIR> *src);
		AXAssignment *readAssignment(std::vector<AXIR> *src);
		std::vector<AXIR> getNextIRLine(std::vector<AXIR> *IRCode);
		AXExpression *readExpression(std::vector<AXIR> src);
		std::vector<std::vector<AXIR> > relex(std::vector<AXIR> src);
};
