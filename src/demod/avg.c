#include <complex.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    complex float in[1];
    long n = 1;
    if (argc > 1)
        n = atol(argv[1]);
    complex float* buf;
    buf = malloc(n * sizeof(complex float));
    if (buf == NULL)
        return -1;
    long i;
    for (i = 0; i < n; i++)
        buf[i] = 0 + 0 * I;
    complex float out[1] = { 0 + 0 * I };
    int index = 0;
    while (1) {
        int k = fread(in, sizeof(complex float), 1, stdin);
        if (feof(stdin))
            break;
        if (k > 0) {
            out[0] -= buf[index];
            buf[index] = in[0];
            out[0] += buf[index];
            index = (index + 1) % n;
            fwrite(out, sizeof(complex float), 1, stdout);
        } else {
            usleep(10);
        }
    }
    free(buf);
    return 0;
}
