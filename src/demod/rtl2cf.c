#include <complex.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 4096
#define DC 127.5

int main()
{
    unsigned char* in;
    in = malloc(N * 2);
    if (in == NULL)
        return -1;
    complex float* out;
    out = malloc(sizeof(complex float) * N);
    if (out == NULL)
        return -2;
    unsigned long i;
    unsigned long k;
    while (1) {
        k = fread(in, 1, N * 2, stdin);
        if (feof(stdin))
            break;
        if (k >= 2 * N) {
            for (i = 0; i < 2 * N; i += 2) {
                out[i / 2] = (in[i] - DC) + (in[i + 1] - DC) * I;
            }
            fwrite(out, sizeof(complex float), N, stdout);
        } else {
            usleep(10);
        }
    }
    free(in);
    free(out);
    return 0;
}
