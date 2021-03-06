#ifndef _AXSTRUCT
#define _AXSTRUCT 1

#include <vector>
#include <string>

/* AX Definitions */
#define TYPE_MARK	0
#define TYPE_VAR	1
#define TYPE_STRING	2
#define TYPE_DNUM	3
#define TYPE_INUM	4
#define TYPE_STRUCT	5
#define TYPE_XLABEL	6
#define TYPE_LABEL	7
#define TYPE_INTCMD	8
#define TYPE_EXTCMD	9
#define TYPE_EXTSYSVAR	10
#define TYPE_CMPCMD	11
#define TYPE_MODCMD	12
#define TYPE_INTFUNC	13
#define TYPE_SYSVAR	14
#define TYPE_PROGCMD	15
#define TYPE_DLLFUNC	16
#define TYPE_DLLCTRL	17
#define TYPE_USERDEF	18

/* AX Lexer Structs */
typedef struct {
	char magic[4];
	int version;
	int maxVal;
	int size;

	int pCS;
	int maxCS;
	int pDS;
	int maxDS;

	int pOT;
	int maxOT;
	int pDINFO;
	int maxDINFO;

	int pLINFO;
	int maxLINFO;
	int pFINFO;
	int maxFINFO;

	int pMINFO;
	int maxMINFO;
	int pFINFO2;
	int maxFINFO2;

	int pHPIDAT;
	short maxHPIDAT;
	short maxVARHPI;
	int bootOption;
	int runtime;
} AXHeader;

typedef struct {
	unsigned short type;
	bool isTop;
	bool isSepr;
	unsigned int code;
	unsigned int jump;
} AXIR;

typedef struct {
	int flag;
	int nameIndex;
	void *hLib;
	int clsid;
} AXLibDat;

typedef struct {
	short index;
	short subId;
	int prmIndex;
	int prmMax;
	int nameIndex;
	int size;
	int OTIndex;
	union {
		void *proc;
		int funcFlag;
	};
} AXStructDat;

typedef struct {
	short mpType;
	short subId;
	int offset;
} AXStructPrm;

typedef struct {
	short flag;
	short option;
	int libName;
	int funcName;
	void *libPtr;
} AXHpiDat;

class AXFile {
	public:
		AXHeader header;
		std::vector<AXIR> code;
		std::vector<int> codePos;
		unsigned char *data;
		std::vector<int> label;
		std::vector<unsigned char> debug;
		std::vector<AXLibDat> libDat;
		std::vector<AXStructDat> structDat;
		std::vector<AXStructPrm> structPrm;
		std::vector<AXHpiDat> hpiDat;
};

/* AX Parser Structs */
struct AXCommand;
typedef enum {
	ADD,
	SUB,
	MUL,
	DIV,
	MOD,
	AND,
	OR,
	XOR,
	EQ,
	NE,
	GT,
	LT,
	GTEQ,
	LTEQ,
	RR,
	LR,
	LEAF
} AXMark;

typedef struct {
	AXMark type;
	union {
		unsigned int id;
		std::string *string;
		struct AXCommand *command;
	};

} AXLeaf;

typedef struct AXBranch {
	enum {
		ADD,
		SUB,
		MUL,
		DIV,
		MOD,
		AND,
		OR,
		XOR,
		EQ,
		NE,
		GT,
		LT,
		GTEQ,
		LTEQ,
		RR,
		LR,
		LEAF
	} type;
	union {
		struct AXBranch *car;
		AXLeaf *car_leaf;
	};
	AXBranch *cdr;
} AXBranch;

typedef struct {
	enum {
		LEAF,
		BRANCH
	} type;
	union {
		AXBranch *branch;
		AXLeaf *leaf;
	};
} AXExpression;

typedef struct AXCommand {
	unsigned short cmdType;
	unsigned int cmdId;
	std::vector<AXExpression *> args;
} AXCommand;

typedef struct {
	unsigned int varId;
	AXMark type;
	AXExpression *expr;
} AXAssignment;

typedef enum {
	COMMAND,
	ASSIGNMENT
} AXStmtType;

typedef struct {
	AXStmtType type;
	union {
		AXCommand *cmd;
		AXAssignment *assign;
	};
} AXStatement;

typedef struct {
	bool read;
	bool write;
	bool infinite;
	int typeCnt;
	int *varTypes;
} AXCmdPrmInfo;

typedef struct {
	unsigned short type;
	unsigned int id;
	const char *name;
	int prmCnt;
	AXCmdPrmInfo *prms;

} AXCmdInfo;

class AXTree{
	public:
		std::vector<AXStatement> code;
		std::vector<int> label;
};
#endif
