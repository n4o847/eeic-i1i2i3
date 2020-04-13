/*
 * 量子化ビット数: 16 bit
 * チャンネル数: 1
 * 標本の符号化方式: signed-integer
 * 標本化周波数: 44100 Hz
 *
 * usage:
 *   ./doremi [A] [n] | play -t raw -b 16 -c 1 -e s -r 44100 -
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

double get_freq(int i) {
    // ドレミファソラシ
    int scale[7] = {0, 2, 4, 5, 7, 9, 11};
    double A4 = 440;
    double freq = A4 * pow(2, 3.0 / 12.0 + i / 7 + scale[i % 7] / 12.0);
    return freq;
}

int main(int argc, char ** argv) {
    if (argc != 3) {
        fprintf(stderr, "argument error\n");
        exit(1);
    }
    double amp = atof(argv[1]);
    int n = atoi(argv[2]);

    for (int i = 0; i < n; i++) {
        double freq = get_freq(i);
        for (int j = 0; j < 13230; j++) {
            short x = amp * sin(2 * M_PI * freq * j / 44100);
            write(STDOUT, &x, 2);
        }
    }
}
