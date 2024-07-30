#include <sys/select.h>
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

int main (int argc, char * argv[]) 
{

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

    int sum_bytes = 0;
    
    for (int i = 1, i < 10, i++)
    {
        pid_t pid = fork();
        int fds[2];
        pipe(fds);
    }

    if (pid = 0)
    {
        close(fds[1]);
        execvp(argv[1], argv+1);
        sum_bytes += ;
        
    }

    if (pid != 0)
    {
        while(!final)   //?
        {
            FD_ZERO(fds[0]);
            FD_SET(fds[0], 15);
            int nfds = select(1024, fds[0], fds[1], NULL, 0);
            FD_ISSET(fds[0], 15);
        }
    }
    


}