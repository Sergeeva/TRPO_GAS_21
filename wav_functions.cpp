#include "./headers/def_types.h"
#include "./headers/wav_functions.hpp"

void readHeader(t_wavhdr* header, FILE* f_in) {
    std::cout << sizeof(*header) << " " << header << std::endl;
    fread(header, sizeof(*header), 1, f_in);

    //Print WAV header
    std::cout << "WAV File Header read:" << std::endl;
    std::cout << "File Type: " << header->chunkID << std::endl;
    std::cout << "File Size: " << header->chunkSize << std::endl;
    std::cout << "WAV Marker: " << header->format << std::endl;
    std::cout << "Format Name: " << header->subchunk1ID << std::endl;
    std::cout << "Format Length: " << header->subchunk1Size << std::endl;
    std::cout << "Format Type: " << header->audioFormat << std::endl;
    std::cout << "Number of Channels: " << header->numChannels << std::endl;
    std::cout << "Sample Rate: " << header->sampleRate << std::endl;
    std::cout << "Sample Rate * Bits/Sample * Channels / 8: " << header->byteRate << std::endl;
    std::cout << "Bits per Sample * Channels / 8.1: " << header->blockAlign << std::endl;
    std::cout << "Bits per Sample: " << header->bitsPerSample << std::endl;
    std::cout << "Subchunk2ID: " << header->subchunk2ID << std::endl;
    std::cout << "Subchunk2Size: " << header->subchunk2Size << std::endl;
}

void readData(double* data_portion, int N, FILE* f_in) {
    int tmp;

    for (int i = 0; i < N; i++){
        fread(&tmp, sizeof(int), 1, f_in);
        data_portion[i] = (double) tmp;
    } 

    return;
}

int calcPortions(t_wavhdr* header, int samples, int N) {
    int portions = samples / N;
    std::cout << "Samples count = " << samples << std::endl;
    std::cout << "Portions count = " << portions << std::endl;

    return portions;
}

int calcTail(int samples, int portions, int N) {
    int tail = samples - N * portions;
    std::cout << "Tail count = " << tail << std::endl;

    return tail;
}

void accumulate(double* acc, double* sq, int N) {
    double c = 4;
    double coeff  = 1 / c;

    for (int j = 0; j < N; ++j) {
        acc[j] = acc[j] * (1 - coeff) + sq[j] * coeff;
    }
}
