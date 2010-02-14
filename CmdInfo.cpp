/*
 * Yet Another HSP Compiler
 *
 * CmdInfo.cpp : IR Command Information Manager
 *
 * Last modified: 2010/02/14
 *
 * Copyright (C) 2010 oksoftware. All rights reserved.
 *
 */

#include "CmdInfo.h"
#include "CmdInfoGen.h"

const char *CmdInfo::typeInfoList[] = { "MARK", "VAR", "STRING", "DNUM", "INUM",
			"STRUCT", "XLABEL", "LABEL", "INTCMD", "EXTCMD",
			"EXTSYSVAR", "CMPCMD", "MODCMD", "INTFUNC", "SYSVAR",
			"PROGCMD", "DLLFUNC", "DLLCTRL", "USERDEF" };

const AXCmdInfo *CmdInfo::findCmdById(unsigned short type, unsigned int id){
	for(int i = 0; i < cmdInfoCnt; i++){
		if(cmdInfoList[i].type == type && cmdInfoList[i].id == id){
			return &cmdInfoList[i];
		}
	}
	return NULL;
}
