#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    long fs = 100000;
    if (argc > 1)
        fs = atol(argv[1]);
    long f = 10000;
    if (argc > 2)
        f = atol(argv[2]);
    complex float* lo;
    lo = malloc(sizeof(complex float) * fs);
    if (lo == NULL)
        return 1;
    complex float* in;
    in = malloc(sizeof(complex float) * fs);
    if (in == NULL)
        return 2;
    complex float* out;
    out = malloc(sizeof(complex float) * fs);
    if (out == NULL)
        return 3;

    long i;
    for (i = 0; i < fs; i++) {
        float p = 2.0 * M_PI / fs * i;
        if (f > 0) {
            lo[i] = cos(p) + sin(p) * I;
        } else {
            lo[i] = cos(p) - sin(p) * I;
        }
    }
    if (f < 0)
        f = -f;
    long loi = 0;
    while (1) {
        long k = fread(in, sizeof(complex float), fs, stdin);
        if (feof(stdin))
            break;
        if (k >= fs) {
            long t;
            for (t = 0; t < fs; t++) {
                out[t] = in[t] * lo[loi];
                loi = (loi + f) % fs;
            }
            fwrite(out, sizeof(complex float), fs, stdout);
        } else {
            usleep(100);
        }
    }
    free(lo);
    free(in);
    free(out);
    fflush(stdout);
    return 0;
}
