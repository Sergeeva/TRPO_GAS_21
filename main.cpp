#include <iostream>
#include <time.h>
#include <sys/time.h>
#include "string.h"
#include "./headers/def_types.h"
#include "./headers/wav_functions.hpp"

#define N_FFT 1024

int main()
{
    const char* file_name = "data/ton_signal_1.wav";
    FILE *f_in = fopen(file_name, "rb");

    if (f_in == NULL) {
        std::cout << "File is NOT opened: " << file_name << std::endl;
        return 1;
    } else {
        std::cout << "File is opened: " << file_name << std::endl;
    }

    const char* output_file_name = "plot/output.dat";
    FILE* f_out = fopen(output_file_name, "w");

    if (f_out == NULL) {
        std::cout << "File or output data is NOT opened: " << output_file_name << std::endl;
        return 1;
    } else {
        std::cout << "File for output data is opened: " << output_file_name << std::endl;
    }

    t_wavhdr header;

    readHeader(&header, f_in);

    int samples = header.subchunk2Size * 8 / (header.bitsPerSample * 2); // subchunk2Size in bytes, bitsPerSample in bits
    int portions;
    int tail;

    portions = calcPortions(&header, samples, N_FFT);
    tail = calcTail(samples, portions, N_FFT);

    double data_portion[N_FFT];
    double sq[N_FFT / 2]; 
    double acc[N_FFT / 2]; 
    memset(data_portion, 0.0, N_FFT * sizeof(double));
    memset(acc, 0.0, N_FFT / 2 * sizeof(double));

    fftw_complex out[N_FFT / 2];
    fftw_plan p;

    struct timeval tv_start, tv_end;
    gettimeofday(&tv_start, NULL);

    p = fftw_plan_dft_r2c_1d(N_FFT, data_portion, out, FFTW_ESTIMATE);

    gettimeofday(&tv_end, NULL);
    printf("Time elapsed for fftw_plan: %ld microsecs \n", (long int)((tv_end.tv_sec-tv_start.tv_sec)*1000000 + (tv_end.tv_usec - tv_start.tv_usec)));

    gettimeofday(&tv_start, NULL);
    for (int i = 0; i < portions; ++i) {
        readData(data_portion, N_FFT, f_in);
        fftw_execute(p);
        for (int k = 0; k < N_FFT / 2; k++) {
            sq[k] = out[k][0] * out[k][0] + out[k][1] * out[k][1];
        }

        accumulate(acc, sq, N_FFT / 2);
    }

    if (tail > 0) {
        memset(data_portion, 0.0, N_FFT * sizeof(double));
        readData(data_portion, tail, f_in );

        fftw_execute(p);
        for (int k = 0; k < N_FFT / 2; k++) {
            sq[k] = out[k][0] * out[k][0] + out[k][1] * out[k][1];
        }

        accumulate(acc, sq, N_FFT / 2);
    }
    
    gettimeofday(&tv_end, NULL);
    printf("Time elapsed for fftw: %ld microsecs \n", (long int)((tv_end.tv_sec-tv_start.tv_sec) * 1000000 + (tv_end.tv_usec - tv_start.tv_usec)) / portions); // !! усредняем

    fftw_destroy_plan(p);

    for (int i = 0; i < N_FFT / 2; ++i) {
        fprintf(f_out, "%f\n", acc[i]);
    }

    fclose(f_in);
    fclose(f_out);

    return 0;
}