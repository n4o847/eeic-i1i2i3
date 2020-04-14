/*
 * raw 形式
 * 量子化ビット数: 16 bit
 * チャンネル数: 1
 * 標本の符号化方式: signed-integer
 * 標本化周波数: 44100 Hz
 *
 * usage:
 *   sox doremi.wav -t raw -b 16 -c 1 -e s -r 44100 - | ./downsample 5 | play -t raw -b 16 -c 1 -e s -r 8820 -
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

#define N 256

void die(char * s) {
    perror(s);
    exit(1);
}

int main(int argc, char ** argv) {
    if (argc != 2) {
        fprintf(stderr, "argument error\n");
        exit(1);
    }
    int n = atoi(argv[1]);

    while (1) {
        short x;
        int c = read(STDIN, &x, 2);
        if (c == -1) die("read");
        if (c == 0) break;
        write(STDOUT, &x, 2);
        for (int i = 0; i < n - 1; i++) {
            int c = read(STDIN, &x, 2);
            if (c == -1) die("read");
            if (c == 0) break;
        }
    }
    return 0;
}
