#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>

#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {

    int fds[2];    
    //fds[0]  read
    //fds[1]  write   
    pipe(fds);
    if (pipe(fds) == -1){
        printf("Opening error");
    }

    pid_t pid = fork();
    if (pid == -1) {
        printf("Fork error");
    }

    if (pid == 0) {                          // child
        dup2(fds[1], STDOUT_FILENO);         // дубликат запишется в файл.дескр. для stdout, т.е. в 1
        close(fds[1]);
        exec();
    } else {                                 //parent
        close(fds[1]);

        // подсчет количества слов
        int symbols = 0;                     //int, because getc returns int type
        int words = 0;
        bool space = true;
        while (true) {
            symbols = getc(fds[0]);          //поочередно считывает символы
            if (feof(fds[0])) break;         //если конец файла
            if (space && !isspace(symbols)) { //проверка символа, пробел он или нет
                words += 1;
                space = false;
            } else if (!space && isspace(symbols)) {
                space = true;
            }
        }
        printf("words: %d \n", words);

        //подсчет количества строк
        int lines = 0;      
        char c;
        while (c != EOF) {
            c = getc(fds[0]);          
            if (c == '\n') lines += 1;
        }
        printf("lines: %d \n", lines);

        //подсчет количества байт
        size_t bytes = sizeof(fds[0]);
        printf("bytes: %lu \n", bytes);

        wait(NULL);
    }
}