#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdbool.h>

void cat(int in, int out) {
    char buf[4096];
    size_t nbyte = 4096;

    while (1) {
        ssize_t a = read(in, buf, nbyte);
        if (a == 0) break;

        ssize_t out = write(in, buf, a);
    }
}


int main(int argc, char * argv[]) {
    if (argc == 1) {
        cat(0, 1);
    } else {
        for (int i=1; i<argc; i++) {
            
            //printf("%s\n", argv[i]);
            int fd = open(argv[i], O_RDONLY);
            cat (fd, 1);
            close(fd);
        }
    }

    //циклический буфер
    struct circular_buf_t {
        uint8_t * buffer;
        size_t head;
        size_t tail;
        size_t max; //of the buffer
        bool full;
    };
    int buffers[16][50]
    ...

    //создание 2-х потоков(нитей)
    int reader() {
        for (i=0; i<50; i++){  //еще j надо варьировать
            read(in, buf[i][j], 4096);
        }
    }
    int writer() { 
        for (i=0; i<50; i++){  //еще j надо варьировать
            write(in, buf[i][j], 4096);
        }       
    }

    pthread_create(&tid, NULL, reader, NULL); //если attr=NULL,то нити создаются с атрибутами по умолчанию.
    pthread_create(&tid, NULL, writer, NULL);
    //После успешного завершения pthread_create() сохраняет идентификатор созданного потока в месте, 
    //на которое ссылается bythread.
    3
    mutex_init(&mp, USYNC_THREAD, NULL);// или mutex_t mp = DEFAULTMUTEX;
    

    bool IsEmpty() {

    }
    bool IsFull() {
        
    }

    if (IsEmpty(buf[i][j])) {
        reader
    }

    //conditions
    
}

