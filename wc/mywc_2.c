#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/errno.h>

int main(int argc, char* argv[]) {
    int fds[2];    
    //fds[0]  read
    //fds[1]  write   
    
    if (pipe(fds) == -1){
        printf("Opening error");
    }

    pid_t pid = fork(); 
    if (pid == -1) {
        printf("Fork error");
        exit(errno);
    }
    
    if (pid == 0) {                          // запуск программы в дочернем процессе
        dup2(fds[1], STDOUT_FILENO);         // дубликат запишется в файл.дескр. для stdout, т.е. в 1
        close(fds[1]);
        close(fds[0]);
        execvp(argv[1],argv+1);              
        
    } else {                                 //parent
        close(fds[1]);

        int words = 0;
        int lines = 0; 
        int bytes = 0;
        int symbols = 0;
        bool space = true;
        char buf[4096];
        size_t nbyte = 4096;  
                    
        while (!0) {                         // считывание до конца входного потока
            int rez = read(fds[0], buf, nbyte);  
            if (rez == 0) {                  //EOF
                break;
            }
            for (int i = 0; i < rez; i++) {
                if (buf[i] == '\n') lines += 1; 
                if (isspace(buf[i])) words += 1; 
            }
            
            // if (space && !isspace(symbols)) { //проверка символа, пробел он или нет
            //     words += 1;
            //     space = false;
            // } else if (!space && isspace(symbols)) {
            //     space = true;
            // }
            

            bytes += rez;
        }
        printf("words: %d \n", words);
        printf("lines: %d \n", lines);
        printf("bytes: %d \n", bytes);

        wait(NULL);
    }
}