#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char* argv[]) { // массив аргв задается системой
    for (int i=1; i<argc; i++) {
        pid_t pid = fork();
        int n = atoi(argv[i]);     //преобразование строки в число
        if (pid == 0) {
            usleep(10000*n);
            printf("%s ",argv[i]); //печать отсортированного массива
            exit(0);               //exit(status)
        }      
    }
    for (int i=1; i<argc; i++) {
        int status;
        wait(&status);             //wait(&status) 
    }
    printf("\n");
}