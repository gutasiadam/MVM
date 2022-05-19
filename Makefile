#
# MVM Makefile - CppHetero Makefile alapján
#
PROG = mvm_with_menu   # a program neve
PROG_O = Address.o mvm_with_menu.o Controller.o String.o Client.o Consumption_announcement.o Invoice.o Tariffs.o# program object fajljai

#PROG_O = main.o # program object fajljai 
PROG_H = mvm_with_menu.cpp Consumption_announcement.cpp Controller.h Controller.cpp Tariffs.h Tariffs.cpp Invoice.h Invoice.cpp Address.h Address.cpp Client.h Client.cpp String.h String.cpp Consumption_Announcement.h Array.hpp # program header fajljai
PROG_L =              # program libjei

MTRACE_O = memtrace.o # memtrace object fajl
MTRACE_H = memtrace.h # memtrace es memcheck header fajlja

CXX = g++   # a C fordito neve
#CXX = clang++ # clang-ot (llvm) is erdemes kiprobalni
CXXFLAGS = -pedantic -Wall -std=c++11 -Werror # kapcsolok: legyen bobeszedu es pedans -c: NHF 3: ne legyen executable.
CXXFLAGS += -ggdb -DMEMTRACE # -DDEBUG : debug mode es legyen debug info is
LDFLAGS = -ggdb # debug a linkelesnel -c

# osszes object, osszes header osszes lib
OBJS = $(PROG_O) $(MTRACE_O)
HEADS = $(PROG_H) $(MTRACE_H)
LIBS = $(PROG_L) 

# alapertelmezett cel: program
.PHONY: all
all: $(PROG)

$(PROG): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@ $(LIBS)

# feltetelezzuk, hogy az osszes obj fugg az osszes headertol
$(OBJS): $(HEADS)

# takaritas igeny szerint
.PHONY: clean
clean:
	rm -f $(OBJS) $(PROG)