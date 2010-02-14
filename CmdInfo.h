/*
 * Yet Another HSP Compiler
 *
 * CmdInfo.cpp : Header of IR Command Information Manager
 *
 * Last modified: 2010/02/14
 *
 * Copyright (C) 2010 oksoftware. All rights reserved.
 *
 */

#include "AXStruct.h"

class CmdInfo {
	public:
		static const char *typeInfoList[];
		static const AXCmdInfo cmdInfoList[];
		static const int cmdInfoCnt;

	public:
		static const char *getTypeName(unsigned short type);
		static const AXCmdInfo *findCmdById(unsigned short type, unsigned int id);
};
