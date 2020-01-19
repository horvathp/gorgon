#include <complex.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    unsigned long n = 1024;
    if (argc > 1)
        n = atol(argv[1]);
    complex float* in;
    in = malloc(sizeof(complex float) * n);
    if (in == NULL)
        return -1;
    unsigned long k;
    unsigned long i;
    complex float out[1];
    while (1) {
        k = fread(in, sizeof(complex float), n, stdin);
        if (feof(stdin))
            break;
        if (k > 0) {
            out[0] = 0 + 0 * I;
            for (i = 0; i < n; i++) {
                out[0] += in[i];
            }
            out[0] /= n;
            fwrite(out, sizeof(complex float), 1, stdout);
        } else {
            usleep(10);
        }
    }
    free(in);
    return 0;
}
