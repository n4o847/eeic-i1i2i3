#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

#define N 256

void die(char * s) {
    perror(s);
    exit(1);
}

int main(int argc, char ** argv) {
    if (argc != 3) {
        fprintf(stderr, "argument error\n");
        exit(1);
    }
    char * ip_addr = argv[1];
    unsigned short port = atoi(argv[2]);

    int s = socket(PF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    inet_aton(ip_addr, &addr.sin_addr);
    addr.sin_port = htons(port);
    int ret = connect(s, (struct sockaddr *)&addr, sizeof(addr));

    unsigned char data[N];
    while (1) {
        int n = read(STDIN, data, N);
        if (n == -1) die("read");
        if (n == 0) break;
        write(s, data, n);
    }

    shutdown(s, SHUT_WR);

    while (1) {
        int n = read(s, data, N);
        if (n == -1) die("read");
        if (n == 0) break;
        write(STDOUT, data, n);
    }

    close(s);

    return 0;
}
