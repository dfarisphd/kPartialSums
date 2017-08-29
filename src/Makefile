## in general, relative paths make me queasy
PWD_DIR:=$(shell pwd)
SPDLOG_INCLUDES:=$(PWD_DIR)/../include/spdlog

CPP_FLAGS:=-I. -I$(SPDLOG_INCLUDES)

CXX:=/usr/bin/g++
CXX_FLAGS:=-Wall -Wextra -std=c++11 -Wno-unused-parameter -pedantic -O0

LD_FLAGS:=-Wall -Wextra -std=c++11 -Wno-unused-parameter -pedantic -O0

all: TestMainDriver

TestMainDriver.o: TestMainDriver.cxx
	$(CXX) $(CPP_FLAGS) $(CXX_FLAGS) -c -o TestMainDriver.o TestMainDriver.cxx

TestMainDriver: TestMainDriver.o
	$(CXX) $(LD_FLAGS) -o TestMainDriver TestMainDriver.o -lm

.PHONY: clean
clean:
	/bin/rm -f TestMainDriver.o

.PHONY: clobber
clobber: clean
	/bin/rm -f TestMainDriver
