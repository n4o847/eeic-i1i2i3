#include <fcntl.h>
#include <unistd.h>

#define N 6

int main() {
    int fd = open("hitoshi", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    unsigned char data[N];
    data[0] = 228;
    data[1] = 186;
    data[2] = 186;
    data[3] = 229;
    data[4] = 191;
    data[5] = 151;
    write(fd, data, N);
    close(fd);
    return 0;
}
