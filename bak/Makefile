PROG:=TestMainDriver1

SOURCES:=\
   KPartialSums.cxx\
   TestMainDriver1.cxx

INCLUDES:=\
   KPartialSums.h

OBJS:=\
   KPartialSums.o\
   TestMainDriver1.o

PROJ_HOME:=$(shell pwd)
INCLUDE_DIR:=$(PROJ_HOME)/include
SRC_DIR:=$(PROJ_HOME)/src
BUILD_DIR:=$(PROJ_HOME)/build
LIB_DIR:=$(PROJ_HOME)/lib

CXX := /usr/bin/g++
CPPFLAGS := -I$(INCLUDE_DIR)
CXXFLAGS := -Wall -Wextra -Wno-unused-parameter -pedantic -std=c++11 -O0

LD_FLAGS := -Wall -Wextra -pedantic -std=c++11 -O0 -L$(LIB_DIR)
## LD_LIBS := -lm -lgtest
LD_LIBS:=

RMF_BIN:=/bin/rm -f
MKDIR_BIN:=/bin/mkdir

all: $(PROG)

KPartialSums.o: KPartialSums.h KPartialSums.cxx
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o KPartialSums.o KPartialSums.cxx

$(PROG).o: $(INCLUDES) $(SOURCES)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $(PROG).o $(PROG).cxx

$(PROG): $(OBJS)
	$(CXX) $(LD_FLAGS) -o $(PROG) $(PROG).o $(OBJS) $(LD_LIBS)


.PHONY: clean
clean:
	$(RMF_BIN) $(OBJS)

clobber: clean
	$(RMF_BIN) $(PROG)
