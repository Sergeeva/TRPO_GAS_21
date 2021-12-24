#ifndef _DEF_WAVFUNCTIONS_
#define _DEF_WAVFUNCTIONS_

#include <iostream>
#include "fftw3.h"

void readHeader(t_wavhdr* header, FILE* f_in);

void readData(double* data_portion, int N, FILE* f_in);

int calcPortions(t_wavhdr* header, int samples, int N);

int calcTail(int samples, int portions, int N);

void accumulate(double* acc, double* sq, int N);

#endif
