CC = g++
STRIP = strip
CFLAGS  = -Wall
LDFLAGS  =

TARGET = yahc
OBJS = yahc.o AXLexer.o dishsp.o CmdInfo.o AXParser.o

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS) $(CFLAGS)
	strip $(TARGET)

clean :
	rm -f $(TARGET) *.o *~ *.exe CmdInfoConv CmdInfoGen.h hsptmp obj

test : $(TARGET)
	.\\$(TARGET) --dishsp-script start.ax

.SUFFIXES: .o .c

.cpp.o:
	$(CC) -c -o $@ $< $(CFLAGS)

yahc.o : yahc.cpp

dishsp.o : dishsp.cpp CmdInfo.h CmdInfoGen.h

AXLexer.o : AXLexer.cpp AXLexer.h AXStruct.h

AXParser.o : AXParser.cpp AXParser.h AXStruct.h

CmdInfo.o : CmdInfo.cpp CmdInfo.h CmdInfoGen.h

CmdInfoGen.h : hsp.cmdinfo CmdInfoConv
	./CmdInfoConv hsp.cmdinfo $@

CmdInfoConv : CmdInfoConv.cpp
	$(CC) -o $@ $< $(LDFLAGS) $(CFLAGS)
