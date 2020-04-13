/*
 * 量子化ビット数: 16 bit
 * チャンネル数: 1
 * 標本の符号化方式: signed-integer
 * 標本化周波数: 44100 Hz
 *
 * usage:
 *   ./sin 10000 440 88200 | play -t raw -b 16 -c 1 -e s -r 44100 -
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

int main(int argc, char ** argv) {
    if (argc != 4) {
        fprintf(stderr, "argument error\n");
        exit(1);
    }
    double amp = atof(argv[1]);
    double freq = atof(argv[2]);
    int n = atoi(argv[3]);

    for (int i = 0; i < n; i++) {
        short x = amp * sin(2 * M_PI * freq * i / 44100);
        write(STDOUT, &x, 2);
    }
}
