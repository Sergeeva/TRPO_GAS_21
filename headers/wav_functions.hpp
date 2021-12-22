#ifndef _DEF_WAVFUNCTIONS_
#define _DEF_WAVFUNCTIONS_

#include <iostream>

void readHeader(t_wavhdr* header, FILE* f_in);

void readData(float* data_portion, int N, FILE* f_in);

int calcPortions(t_wavhdr* header, int samples, int N);

int calcTail(int samples, int portions, int N);

#endif
