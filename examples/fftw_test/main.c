//-*- coding: utf-8 -*-

//******************************************************************************
// Обозначение: main.c 				       
// Назначение:			
// Разработчик: Сергеева Е.И.
// Дата последней корректировки: 
//******************************************************************************

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

#include <fftw3.h>


int main(int argc, char** argv) {

  int N = 512;
  
  fftw_complex *in, *out;
  fftw_plan p;

  in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
  out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);

  struct timeval tv_start, tv_end;
  gettimeofday(&tv_start, NULL);
  p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_PATIENT); // FFTW_ESTIMATE, FFTW_MEASURE
  gettimeofday(&tv_end, NULL);
  printf("Time elapsed for fftw_plan: %ld microsecs \n", (long int)((tv_end.tv_sec-tv_start.tv_sec)*1000000 + (tv_end.tv_usec - tv_start.tv_usec)));
    

  int I = 1000; //вместо количества порций

  gettimeofday(&tv_start, NULL);
  for(int i = 0; i<I; i++){
        fftw_execute(p); /* repeat as needed */
  }
  gettimeofday(&tv_end, NULL);
  printf("Time elapsed for fftw: %ld microsecs \n", (long int)((tv_end.tv_sec-tv_start.tv_sec)*1000000 + (tv_end.tv_usec - tv_start.tv_usec))/I); // !! усредняем
  
  fftw_destroy_plan(p);
  fftw_free(in); fftw_free(out);
  
  return 0;
}
