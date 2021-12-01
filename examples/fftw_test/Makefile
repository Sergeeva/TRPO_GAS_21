#-*- coding: utf-8 -*-

BIN = fftw_test

OBJ = main.o 

CC = gcc

CFLAGS = -g -Wall -MMD 


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
	./fftw_test
