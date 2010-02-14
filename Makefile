CC = g++
STRIP = strip
CFLAGS  = -Wall
LDFLAGS  = 

TARGET = yahc.exe
OBJS = yahc.o AXLexer.o dishsp.o

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS) $(CFLAGS)
	strip $(TARGET)

clean :
	rm -f $(TARGET) *.o *~ *.exe ComInfo.h hsptmp obj

test : $(TARGET)
	.\\$(TARGET) --dishsp start.ax

.SUFFIXES: .o .c

.c.o:
	$(CC) -c -o $@ $<

yahc.o : yahc.cpp

dishsp.o : dishsp.cpp ComInfo.h

AXLexer.o : AXLexer.cpp AXLexer.h AXStruct.h

AXParser.o : AXParser.cpp AXParser.h AXStruct.h

ComInfo.h : cominfo ComInfoConv.exe
	ComInfoConv.exe cominfo $@

ComInfoConv.exe : ComInfoConv.cpp
	$(CC) -o $@ $< $(LDFLAGS) $(CFLAGS)
