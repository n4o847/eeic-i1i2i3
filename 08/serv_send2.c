#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>

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
    unsigned short port = atoi(argv[1]);

    int ss = socket(PF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(ss, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        die("bind");
    }

    if (listen(ss, 10) == -1) {
        die("listen");
    }

    struct sockaddr_in client_addr;
    socklen_t len = sizeof(struct sockaddr_in);
    int s = accept(ss, (struct sockaddr *)&client_addr, &len);

    close(ss);

    FILE * fp;
    if ((fp = popen("rec -t raw -b 16 -c 1 -e s -r 44100 -", "r")) == NULL) {
        die("popen");
    }

    unsigned char data[N];
    while (1) {
        int n = fread(data, sizeof(* data), N, fp);
        if (n == -1) die("fread");
        if (n == 0) break;
        write(s, data, n);
    }

    close(s);
    pclose(fp);

    return 0;
}
