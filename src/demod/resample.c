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
    long i = 0;
    while (1) {
        int k = fread(in, sizeof(complex float), 1, stdin);
        if (feof(stdin))
            break;
        if (k > 0) {
            if (n > 0) {
                for (i = 0; i < n; i++)
                    fwrite(in, sizeof(complex float), 1, stdout);
            } else {
                i = (i + 1) % n;
                if (i == 0) {
                    fwrite(in, sizeof(complex float), 1, stdout);
                    fflush(stdout);
                }
            }
        } else {
            usleep(10);
        }
    }
    return 0;
}
