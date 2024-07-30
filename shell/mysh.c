#include <unistd.h>
#include <stdio.h>
#include <sys/types.h> 
#include <string.h>
#include <stdlib.h>

int parse_str(char *string_from_stdin)
{ 
    char* cmd = strtok(string_from_stdin, "|");
    int num_cmd = 0;
    char** comands[num_cmd] = {0};  //в этот массив строк будем записывать названия каждой команды 
    void* mem_block_comands = calloc(num_cmd, sizeof(char*));
    while (cmd != NULL)
    { 
        printf("%s\n", cmd);
        cmd = strtok(NULL, "|");
        comands[num_cmd] = cmd;
        num_cmd++;
    }
    printf("num_cmd = %d\n", num_cmd);
    return num_cmd;
    // for (unsigned iter = 0; iter < i; iter++)
    // {
    //     fprintf(stderr, "commands[%u] is |%s| \n", iter, commands[iter]);
    // }
}

char* parse_cmd(struct Prog* cmd, int num_cmd, void* mem_block)
{
    char* arg[100] = {0};
    for (int i = 0; i < num_cmd; i++)
    {
        char * cmd_arg = strtok(cmd, " ");
        while (cmd_arg != NULL)
        {
            printf("%s\n", cmd_arg);
            cmd_arg = strtok(NULL, " ");
        }
        arg[i] = cmd_arg;
        printf("%s\n", cmd_arg);
    }
    return arg;
}

int main(int argc, char *argv[]) 
{
    char buf[256] = {0};            
    if (fgets(buf, sizeof(buf), stdin) == NULL)    //чтение строки из stdin в буфер
    {
        printf("Error  with fgets");
        exit(EXIT_FAILURE);
    }

    int len = strlen(buf);
    buf[len-1] = 0;                       // убираем /n из введенной строки
    len--;                                // убираем /n из введенной строки
    
    printf("str=[%s], [%d]\n", buf, len); 
    int num_cmd = parse_str(buf);         //разделяем введенную строку по "|" на команды и записываем количество таких команд

    struct Prog
    {
        char* cmd;                        //команда
        char** cmd_arg;                   //аргументы команды
    };

    void* mem_block = calloc(num_cmd, sizeof(struct Prog));       //создали динамический блок памяти, который создается "по факту", а не автоматисески при запуске программы; для того, чтобы размер такого блока был ни больше ни меньше нужного нам
    if (mem_block == NULL) 
    {
        fprintf(stderr, "Error with creating a memory block");
        exit(-1);
    }
    
    struct Prog* cmd = (struct Prog*) mem_block;
    parse_cmd(cmd, num_cmd, mem_block);

    // int fds[2];
    // pipe(fds);

    // pid_t pid = fork();
    
    // if (pid == 0) 
    // {      
    //     //перенаправить stdin/stdout в pipe
    //     dup2(fds[1], STDOUT_FILENO); 
    //     close(fds[1]);
    //     close(fds[0]);
    //     execvp(cmd, cmd_arg); 
    // }
    // else 
    // {
    //     close (fds[0]);
    //     close(fds[1]);
    //     //wait(NULL);
    // } 
    free(mem_block);                            //освобождение созданной динамической памяти
}










   