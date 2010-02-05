#ifndef _AXSTRUCT
#define _AXSTRUCT 1

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
	unsigned short jump;
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
#endif
