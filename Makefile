CC = g++
STRIP = strip
CFLAGS  = -Wall
LDFLAGS  = 

YAHC_TARGET = yahc.exe
YAHC_OBJS = yahc.o AXLexer.o

DISHSP_TARGET = dishsp.exe
DISHSP_OBJS = dishsp.o AXLexer.o

all : $(YAHC_TARGET) $(DISHSP_TARGET)

$(YAHC_TARGET) : $(YAHC_OBJS)
	$(CC) -o $(YAHC_TARGET) $(YAHC_OBJS) $(LDFLAGS) $(CFLAGS)
	strip $(YAHC_TARGET)

$(DISHSP_TARGET) : $(DISHSP_OBJS)
	$(CC) -o $(DISHSP_TARGET) $(DISHSP_OBJS) $(LDFLAGS) $(CFLAGS)
	strip $(DISHSP_TARGET)

clean :
	rm -f $(YAHC_TARGET) *.o *~
	rm -f $(DISHSP_TARGET) *.o *~

test : $(DISHSP_TARGET)
	.\\$(DISHSP_TARGET) start.ax

.SUFFIXES: .o .c

.c.o:
	$(CC) -c -o $@ $<

yahc.o : yahc.cpp

dishsp.o : dishsp.cpp

AXLexer.o : AXLexer.cpp AXLexer.h AXStruct.h

