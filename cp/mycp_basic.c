#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

void cp(size_t in, size_t trg_fd){
    char buf[4097];
    size_t nbyte = 4096;
    ssize_t num_bytes = read(in, buf, nbyte); 
    buf[4096] = 0;
    while (num_bytes == 4096) {
        //fprintf(trg_fd, "%s", buf);
        write(trg_fd, buf, num_bytes);
        num_bytes = read(in, buf, nbyte);
    }
    //fprintf(trg_fd, "%s", buf);
    write(trg_fd, buf, num_bytes);
    
}

int main() {
    
    size_t src_fd = open("a.txt", O_RDONLY);
    size_t trg_fd = open("b.txt", O_WRONLY | O_CREAT | O_TRUNC); 

    cp(src_fd, trg_fd);
    
    close(src_fd);
    //close(trg_fd);     
}