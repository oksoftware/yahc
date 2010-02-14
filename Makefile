CC = g++
STRIP = strip
CFLAGS  = -Wall
LDFLAGS  = 

TARGET = yahc.exe
OBJS = yahc.o AXLexer.o dishsp.o CmdInfo.o

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS) $(CFLAGS)
	strip $(TARGET)

clean :
	rm -f $(TARGET) *.o *~ *.exe CmdInfoGen.h hsptmp obj

test : $(TARGET)
	.\\$(TARGET) --dishsp start.ax

.SUFFIXES: .o .c

.c.o:
	$(CC) -c -o $@ $<

yahc.o : yahc.cpp

dishsp.o : dishsp.cpp CmdInfo.h CmdInfoGen.h

AXLexer.o : AXLexer.cpp AXLexer.h AXStruct.h

AXParser.o : AXParser.cpp AXParser.h AXStruct.h

CmdInfo.o : CmdInfo.cpp CmdInfo.h CmdInfoGen.h

CmdInfoGen.h : hsp.cmdinfo CmdInfoConv.exe
	CmdInfoConv.exe hsp.cmdinfo $@

CmdInfoConv.exe : CmdInfoConv.cpp
	$(CC) -o $@ $< $(LDFLAGS) $(CFLAGS)
