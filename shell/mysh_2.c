#include <unistd.h>
#include <stdio.h>
#include <sys/types.h> 
#include <string.h>
#include <stdlib.h>

int calc_tokens_num (char *string_from_stdin)
{
    char separators[2];
    separators[0] = '|';
    separators[1] = ' ';
    int num_cmd = 1;
    int i = 0;
    while (string_from_stdin[i] != 0)
    { 
        if (string_from_stdin[i] == '|') num_cmd++;
        i++;
    }
    printf("num_cmd = %d\n", num_cmd);

    return num_cmd;
}

char** parse_str(char *string_from_stdin, char** commands)
{ 
    char* cmd = strtok(string_from_stdin, "|");  

    commands[0] = cmd;
    int i = 1;
    while (cmd != NULL)
    {
        commands[i] = cmd;
        //printf("%s\n", commands[i]);
        cmd = strtok(NULL, "|");
        i++;
    }
    return commands;
}

int calc_arg_num(char* cmd_with_args)              /////////////////////////for each command
{
    int num_arg = 0;
    int i = 0;
    while (*cmd_with_args != 0)
    { 
        if (*cmd_with_args == ' ') num_arg++;
        cmd_with_args++;
    }
    //printf("num_arg = %d\n", num_arg);

    return num_arg;
}

// void parse_cmd(char** commands, char*** arguments)
// {
//     char* arg = strtok(*commands, " ");
//     arguments[0] = &arg;
//     int i = 1;

//     while (arg != NULL)
//     {
//         arguments[i] = &arg;
//         printf("%s\n", *arguments[i]);
//         arg = strtok(NULL, " ");
//         i++;
//     }
//     //return arg;
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
    
    int num_cmd = calc_tokens_num(buf);
    char** mem_commands_with_args = (char**)calloc(num_cmd, sizeof(char*) );   //в этот массив строк будем записывать названия каждой команды с ее аргументами
    char** commands = parse_str(buf, mem_commands_with_args);                  //массив строк с командами и их аргументами

    for (int i = 1; i <= num_cmd; i++) printf("%s\n", commands[i]);          //печать введенных команд с их аргументами

    for (int i = 1; i <= num_cmd; i++)
    {
        int num_arg = calc_arg_num(commands[i]);
        printf("num_arg = %d\n", num_arg);
    }
 

    // char*** mem_arguments = (char***)calloc(num_arg, sizeof(char*));    ///////////////////////////
    // char*** arguments = parse_cmd(commands, mem_arguments);
    // for (int i = 1; i <= num_arg; i++)
    // {
    //     printf("%s\n", arguments[i]);
    // }


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
    //free(mem_commands_with_args);                            //освобождение созданной динамической памяти
}










   