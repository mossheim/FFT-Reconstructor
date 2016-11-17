#include "fftw3.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void print_fftw(fftw_complex* parr, int n);
void fftw_fill_rand(fftw_complex* parr, int n, double min, double max);
void fftw_fill_sine(fftw_complex* parr, int n, double cycles, double offset);
void fftw_r2p(fftw_complex* parr, int n);
double frand(double, double);

int main() {
    fftw_complex *in, *out, *ptr;
    fftw_plan p;
    srand(2u);
    
    int N = 512;
    
    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
    p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    
//    fftw_fill_rand(in, N, -1.0, 1.0);
    fftw_fill_sine(in, N, 8.0, 0.25);
    
    fftw_execute(p);
    print_fftw(in, N);
    print_fftw(out, N);
    fftw_r2p(out, N);
    print_fftw(out, N);
    
    fftw_destroy_plan(p);
    fftw_free(in), fftw_free(out);
    
    printf("worked.\n");
    return 0;
}

void print_fftw(fftw_complex* parr, int n) {
    for(int i = 0; i < n; i++, parr++) {
        printf("%d %f %f\n", i, (*parr)[0], (*parr)[1]);
    }
}

void fftw_fill_rand(fftw_complex* parr, int n, double min, double max) {
    for(; n > 0; n--, parr++)
        (*parr)[0] = frand(min, max);
}

void fftw_fill_sine(fftw_complex* parr, int n, double freq, double phase) {
    for(int i = 0; i < n; i++, parr++) {
        (*parr)[0] = sin(2 * M_PI * (i * freq / n + phase));
    }
}

double frand(double min, double max) {
    double f = (double)rand() / RAND_MAX;
    return min + f * (max - min);
}

void fftw_r2p(fftw_complex* parr, int n) {
    for(; n>0; n--, parr++) {
        double real = (*parr)[0];
        (*parr)[0] = atan2((*parr)[1], real);
        (*parr)[1] = sqrt(pow((*parr)[1], 2.0) + pow(real, 2.0));
    }
}
