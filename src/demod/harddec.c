/* Hard-decision by ha7wen
// Input: 2 complex number / databit
// (da) 1st shifted into a, (db) 2nd into b uint16
// Output: if a == SYNC or b == SYNC form the output hexa string as binary demodulated
data (packetlength bytes)
*/

#include <complex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define SYNC 0x2dd4

char* ts()
{
    time_t t;
    time(&t);
    return ctime(&t);
}

void readfile(char* x, unsigned long* k)
{
    FILE* f = fopen(x, "r");
    if (f != NULL) {
        unsigned long p = 0;
        int n = fread(&p, sizeof(unsigned long), 1, f);
        if (n > 0) {
            *k = p * 8;
            fprintf(stderr, "### read packet length = %ld B\n", p);
            fflush(stderr);
            fclose(f);
        }
    }
}


int main(int argc, char** argv)
{
    unsigned long n = 70;
    if (argc > 1)
        n = atol(argv[1]);
    n *= 8;
    complex float in[2];
    uint16_t a = 0, b = 0;
    uint8_t sm = 0, da = 0, db = 0;
    uint32_t ca = 0, cb = 0;
    uint8_t d = 0;
    unsigned long cntr = 0;
    while (1) {
        int k = fread(in, sizeof(complex float), 2, stdin);
        if (feof(stdin))
            break;
        if (k > 0) {
            da = (creal(in[0]) > cimag(in[0]));
            db = (creal(in[1]) > cimag(in[1]));
            if (sm == 1) {
                d = (d << 1) | da;
                ca++;
                if (ca % 8 == 0)
                    printf("%.2X", d);
                if (ca >= n) {
                    sm = 0;
                    ca = 0;
                    //					printf(",%ld\r\n",time(NULL));
                    printf(" RSSI -132 dBm %s", ts());
                    fflush(stdout);
                }
            }
            if (sm == 2) {
                d = (d << 1) | db;
                cb++;
                if (cb % 8 == 0)
                    printf("%.2X", d);
                if (cb >= n) {
                    sm = 0;
                    cb = 0;
                    //					printf(",%ld\r\n",time(NULL));
                    printf(" RSSI -132 dBm %s", ts());
                    fflush(stdout);
                }
            }
            if (sm == 0) {
                a = (a << 1) | da;
                b = (b << 1) | db;
            }
            if (a == SYNC && ca == 0 && sm == 0)
                sm = 1;
            if (b == SYNC && cb == 0 && sm == 0)
                sm = 2;
        } else {
            usleep(1000);
        }
        if (cntr == 0) {
            readfile(argv[2], &n);
        }
        cntr = (cntr + 1) % 1000;
    }
    printf("\r\n");
    return 0;
}
