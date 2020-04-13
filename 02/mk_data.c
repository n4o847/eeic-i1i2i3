#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define N 256

int main(int argc, char ** argv) {
    if (argc != 2) {
        fprintf(stderr, "argument error\n");
        exit(1);
    }
    int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    unsigned char data[N];
    for (int i = 0; i < N; i++) {
        data[i] = i;
    }
    write(fd, data, N);
    close(fd);
    return 0;
}
