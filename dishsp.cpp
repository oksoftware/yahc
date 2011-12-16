/*
 * Yet Another HSP Compiler
 *
 * dishsp.cpp : HSP IR Code Disassembler
 *
 * Last modified: 2010/02/21
 *
 * Copyright (C) 2010 oksoftware. All rights reserved.
 *
 */

#include <iostream>
#include <iomanip>
#include <sstream>
#include "dishsp.h"
#include "AXLexer.h"
#include "AXParser.h"
#include "CmdInfo.h"

Dishsp::Dishsp(std::ostream *out, int mode){
	using namespace std;
	this->out = out;
	this->mode = mode;

	if(mode == Dishsp::MODE_AXIR){
		*out<<"oksoftware HSP 3.2 AX Dumper"<<endl
		    <<"Copyright(C) 2010 oksoftware. All rights reserved."<<endl<<endl
		    <<"Dumping to AX IR Code..."<<endl<<endl;
	}else if(mode == Dishsp::MODE_SCRIPT){
		*out<<"//oksoftware HSP 3.2 AX Dumper"<<endl
		    <<"//Copyright(C) 2010 oksoftware. All rights reserved."<<endl<<endl
		    <<"//Dumping to HSP Script Code..."<<endl<<endl;
	}
	return;
}

void Dishsp::setInput(std::istream *in){
	this->in = in;
	return;
}

void Dishsp::write(){
	AXLexer lexer(in);
	lexer.lex();

	if(mode == Dishsp::MODE_AXIR){
		writeHeader(&lexer.header);
		writeIRs(&lexer);
		writeLINFOs(&lexer);
		writeSTRUCTDATs(&lexer);
		writeSTRUCTPRMs(&lexer);
		writeHPIDATs(&lexer);
	}else if(mode == Dishsp::MODE_SCRIPT){
		AXParser parser(&lexer);
		parser.parse();
	}

	return;
}

void Dishsp::writeHeader(AXHeader *header){
	using namespace std;

	*out<<"AX FILE HEADER"<<endl;
	*out<< hex << right <<
		"\t" << setw(8) << *((unsigned int *)header->magic) << " Magic Code 'HSP3'" << endl <<
		"\t" << setw(8) << header->version << " Version Number Info" << endl <<
		"\t" << setw(8) << header->maxVal << " Max Count of VAL Object" << endl <<
		"\t" << setw(8) << header->size << " Total File Size" << endl <<

		"\t" << setw(8) << header->pCS << " Ptr to Code Segment" << endl <<
		"\t" << setw(8) << header->maxCS << " Size of Code Segment" << endl <<
		"\t" << setw(8) << header->pDS << " Ptr to Data Segment" << endl <<
		"\t" << setw(8) << header->maxDS << " Size of Data Segment" << endl <<

		"\t" << setw(8) << header->pOT << " Ptr to Object Temp" << endl <<
		"\t" << setw(8) << header->maxOT << " Size of Object Temp" << endl <<
		"\t" << setw(8) << header->pDINFO << " Ptr to Debug Info" << endl <<
		"\t" << setw(8) << header->maxDINFO << " Size of Debug Info" << endl <<

		"\t" << setw(8) << header->pLINFO << " Ptr to LibInfo" << endl <<
		"\t" << setw(8) << header->maxLINFO << " Size of LibInfo" << endl <<
		"\t" << setw(8) << header->pFINFO << " Ptr to FuncInfo" << endl <<
		"\t" << setw(8) << header->maxFINFO << " Size of FuncInfo" << endl <<

		"\t" << setw(8) << header->pMINFO << " Ptr to ModInfo" << endl <<
		"\t" << setw(8) << header->maxMINFO << " Size of ModInfo" << endl <<
		"\t" << setw(8) << header->pFINFO2 << " Ptr to FuncInfo2" << endl <<
		"\t" << setw(8) << header->maxFINFO2 << " Size of FuncInfo2" << endl <<

		"\t" << setw(8) << header->pHPIDAT << " Ptr to HPIDAT" << endl <<
		"\t" << setw(8) << header->maxHPIDAT << " Size of HPIDAT" << endl <<
		"\t" << setw(8) << header->maxVARHPI << " Num of Vartype Plugins" << endl <<
		"\t" << setw(8) << header->bootOption << " Bootup Options" << endl <<
		"\t" << setw(8) << header->runtime << " Ptr to Runtime Name" << endl << endl;
	return;
}

void Dishsp::writeIRs(AXFile *axfile){
	using namespace std;
	const char *markName[] = { "+", "-", "*", "/", "%", "&", "|", "^", "=", "!=", ">", "<", ">=", "<=", ">>", "<<"};
	int cnt = 0;

	*out<<"CODE SEGMENT"<<endl<<endl;

	for(int i = 0; i < (int)axfile->code.size(); i++){
		AXIR *cur;
		cur = &(axfile->code.at(i));

		/* Labels */
		for(int j = 0; j < (int)axfile->label.size(); j++){
			if(axfile->label.at(j) == i){
				*out<<"*label"<<dec<<j<<endl;
			}
		}


		/* Current Bytes of the IR */
		*out<<"  "<<hex<<right<<setw(8)<<setfill('0')<<axfile->codePos.at(i);
		/* Current count of it */
		*out<<hex<<right<<"("<<setw(8)<<setfill(' ')<<cnt<<"): ";
		/* Status of the IR */
		*out<<(cur->isTop ? "^" : " ")<<" "<<(cur->isSepr ? "," : " ")<<" ";
		/* hex dump and name of Type number */
		*out<<hex<<right<<setw(4)<<cur->type<<" ";
		const char *typeName = CmdInfo::getTypeName(cur->type);
		if(typeName != NULL) *out<<paddingString(string(CmdInfo::getTypeName(cur->type)), 10);

		/* hex dump of command id */
		*out<<hex<<right<<setw(8)<<cur->code<<" ";
		/* name of the command */
		const AXCmdInfo *curCmdInfo = CmdInfo::findCmdById(cur->type, cur->code);
		if(curCmdInfo != NULL) *out<<curCmdInfo->name;
		switch(cur->type){
			case TYPE_MARK:
				if(cur->code < (sizeof(markName) / sizeof(char *))) *out<<markName[cur->code];
				break;
			case TYPE_CMPCMD:
				*out<<"(jump to "<<cur->jump<<")";
				break;
			case TYPE_LABEL:
				*out<<"*label"<<dec<<cur->code;
				break;
			case TYPE_STRING:
				*out<<"\""<<&(axfile->data[cur->code])<<"\"";
				break;
		}



		*out<<endl;
		cnt++;
	}

	*out<<endl;

	return;
}

std::string Dishsp::paddingString(std::string src, unsigned int size){
	std::string padding("");
	if(src.size() < size){
		for(unsigned int i; i < (size - src.size()); i++) padding += " ";
	}
	return src + padding;
}

void Dishsp::writeLINFOs(AXFile *axfile){
	using namespace std;

	*out<<"LIB INFO"<<endl<<endl;

	for(unsigned int i = 0; i < axfile->libDat.size(); i++){
		AXLibDat cur = axfile->libDat.at(i);
		*out<<"LIBDAT #"<<dec<<i<<endl;
		*out<<hex<<right
			<<setw(8)<<cur.flag<<" Flags"<<endl
			<<setw(8)<<cur.nameIndex<<" Name Index \""<<&(axfile->data[cur.nameIndex])<<"\""<<endl
			<<setw(8)<<(unsigned int)cur.hLib<<" Handle of Lib"<<endl
			<<setw(8)<<cur.clsid<<" CLSID"<<endl<<endl;
	}

	*out<<endl;

	return;
}

void Dishsp::writeSTRUCTDATs(AXFile *axfile){
	using namespace std;

	*out<<"FUNC INFO"<<endl<<endl;

	for(unsigned int i = 0; i < axfile->structDat.size(); i++){
		AXStructDat cur = axfile->structDat.at(i);
		*out<<"STRUCTDAT #"<<dec<<i<<endl;
		*out<<hex<<right
			<<setw(8)<<cur.index<<" LIBDAT Index"<<endl
			<<setw(8)<<cur.subId<<" Struct Index"<<endl
			<<setw(8)<<cur.prmIndex<<" STRUCTPRM(MINFO) Index"<<endl
			<<setw(8)<<cur.prmMax<<" Count of STRUCTPRM"<<endl
			<<setw(8)<<cur.nameIndex<<" Name Index \""<<&(axfile->data[cur.nameIndex])<<"\""<<endl
			<<setw(8)<<cur.size<<" Struct(Stack) Size"<<endl
			<<setw(8)<<cur.OTIndex<<" [MODULE]OT Index / [DLL] Cleanup Flags"<<endl
			<<setw(8)<<cur.funcFlag<<" [MODULE]Func Flag / [DLL] Ptr to Proc"<<endl<<endl;
	}

	*out<<endl;

	return;
}

void Dishsp::writeSTRUCTPRMs(AXFile *axfile){
	using namespace std;

	*out<<"MOD INFO"<<endl<<endl;

	for(unsigned int i = 0; i < axfile->structPrm.size(); i++){
		AXStructPrm cur = axfile->structPrm.at(i);
		*out<<"STRUCTPRM #"<<dec<<i<<endl;
		*out<<hex<<right
			<<setw(8)<<cur.mpType<<" Parameter Type"<<endl
			<<setw(8)<<cur.subId<<" Struct Index"<<endl
			<<setw(8)<<cur.offset<<" Offset"<<endl<<endl;
	}

	*out<<endl;

	return;
}

void Dishsp::writeHPIDATs(AXFile *axfile){
	using namespace std;

	*out<<"HPI INFO"<<endl<<endl;

	for(unsigned int i = 0; i < axfile->hpiDat.size(); i++){
		AXHpiDat cur = axfile->hpiDat.at(i);
		*out<<"HPIDAT #"<<dec<<i<<endl;
		*out<<hex<<right
			<<setw(8)<<cur.flag<<" Flags"<<endl
			<<setw(8)<<cur.option<<" Options"<<endl
			<<setw(8)<<cur.libName<<" Library Name"<<endl
			<<setw(8)<<cur.funcName<<" Func Name"<<endl
			<<setw(8)<<(int)cur.libPtr<<" Ptr to Lib"<<endl<<endl;
	}

	*out<<endl;

	return;
}
