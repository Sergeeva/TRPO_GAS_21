#-*- coding: utf-8 -*-

BIN = wav_reader

OBJ = main.o wav_functions.o

CC = g++

CFLAGS = -g -Wall 


CC_DEFINES	+=  -D_TECH 

all: $(BIN)

$(BIN): $(OBJ) 
	$(CC) $(CFLAGS) $(CC_DEFINES)  $(OBJ) -o $(BIN) -lfftw3 -lm

include $(wildcard *.d)

.PHONY : clean

clean:
	rm -f $(BIN) *.o *.d
	rm -f *.dat *.log *.txt  
	rm -f *~ \#*\# *.cache log

run:
	./wav_reader
