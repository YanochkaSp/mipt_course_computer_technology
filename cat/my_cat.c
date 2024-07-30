#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>

void cat(int in, int out) {
    char buf[4096];
    size_t nbyte = 4096;

    while (1) {
        ssize_t a = read(in, buf, nbyte);
        if (a == 0) break;

        ssize_t out = write(in, buf, a);
    }

}

int main(int ac, char * av[]) {
    if (ac == 1) {
        cat(0, 1);
    } else {
        for (int i=1; i<ac; i++) {
            
            //printf("%s\n", av[i]);
            int fd = open(av[i], O_RDONLY);
            cat (fd, 1);
            close(fd);
        }
    }

}
