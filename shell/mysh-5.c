#include <unistd.h>
#include <stdio.h>

#include <sys/types.h> 
#include <string.h>
#include <stdlib.h>

int calc_tokens_num (char *string_from_stdin)
{
    int num_cmd = 1;
    int i = 0;
    while (string_from_stdin[i] != 0)
    { 
        //cmd = strtok(NULL, "|");
        if (string_from_stdin[i] == '|') num_cmd++;
        i++;
    }
    printf("num_cmd = %d\n", num_cmd);

    return num_cmd;
}

void parse_str(char *string_from_stdin, char** commands)
{ 
    char* cmd = strtok(string_from_stdin, "|");
    
    commands[0] = cmd;
    int i = 1;
    while (cmd != NULL)
    {
        printf("%s\n", cmd);
        cmd = strtok(NULL, "|");
        commands[i] = cmd;
        i++;
    }
    printf("%s\n", commands[1]);
}

// char* parse_cmd(struct Prog* cmd, int num_cmd, void* mem_block)
// {
//     char* arg[100] = {0};
//     for (int i = 0; i < num_cmd; i++)
//     {
//         char * cmd_arg = strtok(cmd, " ");
//         while (cmd_arg != NULL)
//         {
//             printf("%s\n", cmd_arg);
//             cmd_arg = strtok(NULL, " ");
//         }
//         arg[i] = cmd_arg;
//         printf("%s\n", cmd_arg);
//     }
//     return arg;
// }

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
             //разделяем введенную строку по "|" на команды и записываем количество таких команд

    struct Prog
    {
        char* commands;                        //команда
        char** cmd_arg;                   //аргументы команды
    };

    struct Prog* commands;

    int num_cmd = calc_tokens_num(buf);
    char** commands_with_args = (char**)calloc(num_cmd, sizeof(char*) );  //в этот массив строк будем записывать названия каждой команды 
    parse_str(buf, commands_with_args);

    void* mem_block = calloc(num_cmd, sizeof(struct Prog));       //создали динамический блок памяти, который создается "по факту", а не автоматисески при запуске программы; для того, чтобы размер такого блока был ни больше ни меньше нужного нам
    if (mem_block == NULL) 
    {
        fprintf(stderr, "Error with creating a memory block");
        exit(-1);
    }

    //parse_cmd(comands, num_cmd, mem_block);

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










   