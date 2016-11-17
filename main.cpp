#include "fftw3.h"
#include <stdio.h>

int main() { printf("hello world!\n"); return 0; }
int main() {
    fftw_complex *in, *out, *ptr;
    fftw_plan p;
    srand(2u);
    
    int N = 512;
    
    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
    p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(p);
    fftw_destroy_plan(p);
    fftw_free(in), fftw_free(out);
    
    printf("worked.\n");
    return 0;
}
