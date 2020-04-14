/* 
 * downsample.c
 *
 * usage:
 *   ./downsample [n]
 *   sox doremi.wav -t raw -b 16 -c 1 -e s -r 44100 - | ./downsample 5 | play -t raw -b 16 -c 1 -e s -r 8820 -
 *
 * 16 bit のモノラルの raw データを標準入力から受け取って、
 * それを与えられた割合で間引いて標準出力に出す。
 *
 * raw 形式
 * 量子化ビット数: 16 bit
 * チャンネル数: 1
 * 標本の符号化方式: signed-integer
 * 標本化周波数: 44100 Hz
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

    for (int i = 0; ; i++) {
        short x;
        int c = read(STDIN, &x, 2);
        if (c == -1) die("read");
        if (c < 2) break;
        if (i % n == 0) {
            write(STDOUT, &x, 2);
        }
    }
    return 0;
}
