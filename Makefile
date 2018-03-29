PROGRAM=hexcape.bin
BUILD_DIR=Build.lnx
SRC_DIR=src
GPP=g++
GCC=gcc
FLAGS=-Iheaders -fshow-column  -g2 -Wall -O0  -D_DEBUG -g -std=c++11
LIBS=-lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system

include Makefile.common

.PHONY: clean
clean:
	rm -f $(BUILD_DIR)/*.o $(PROGRAM)

.PHONY: cleandep
cleandep:
	rm -f $(BUILD_DIR)/*.d
