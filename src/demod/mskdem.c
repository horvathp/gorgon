#include <complex.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LL 32

int main()
{
    complex float m = 0 + 0 * I;
    complex float in[1];
    complex float out[1];
    float t = 0 + 0 * I;
    float x = 0 + 0 * I;
    while (1) {
        int k = fread(in, sizeof(complex float), 1, stdin);
        if (feof(stdin))
            break;
        if (k > 0) {
            t = cimag(in[0] * conj(m));
            m = in[0];
            x = 1. / LL * t + (LL - 1.0) / LL * x;
            out[0] = t + x / 2 * I;
            fwrite(out, sizeof(complex float), 1, stdout);
        } else {
            usleep(100);
        }
    }
    return 0;
}
