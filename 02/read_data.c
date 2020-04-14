/* 
 * read_data.c
 *
 * usage:
 *   ./read_data [file]
 *
 * [file] を開き、何バイト目が何という
 * バイトだったかを 2 カラムで表示する。
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

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
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) die("open");
    unsigned char data[N];
    int offset = 0;
    while (1) {
        int n = read(fd, data, N);
        if (n == -1) die("read");
        if (n == 0) break;
        for (int i = 0; i < n; i++) {
            printf("%d %d\n", offset + i, data[i]);
        }
        offset += n;
    }
    close(fd);
    return 0;
}
