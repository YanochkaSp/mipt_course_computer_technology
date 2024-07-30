#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h> 
#include <string.h>

void parse_cmd(char* cmdTrue) 
{
    char cmd[1000] = {0};
    memcpy(cmd, cmdTrue, strlen(cmdTrue));     //скопировали кусок памяти, чтобы указатель не показывал на ложный ноль 
    char * cmd_arg[100] = {0};  
    int len_cmd = strlen(cmd);

    for (char* p = cmd; *p != 0; p++)
    {
        if (*p == ' ')
        {
            *p = 0;
        }
    }
    printf("cmd=[%s]\n", cmd);
    for (int index = 0; index < len_cmd; index++)
    {
        char* p = cmd + index;
        if (*p == 0)          //////////////////////////////////////исправить с учетом пробелов
        {

            cmd_arg[index] = p + 1;
            printf("arg=[%s]\n", cmd_arg[index]);
            index++;
        }
    }

    int fds[2];
    pipe(fds);

    pid_t pid = fork();
    
    if (pid == 0) 
    {      
        //перенаправить stdin/stdout в pipe
        dup2(fds[1], STDOUT_FILENO); 
        close(fds[1]);
        close(fds[0]);
        execvp(cmd, cmd_arg); 
    }
    else 
    {
        close (fds[0]);
        close(fds[1]);
        //wait(NULL);
    }    
     
    
}

int main(int argc, char *argv[]) 
{
    char arguments[256];
    fgets(arguments, sizeof(arguments), stdin); //возвращают символ, считанный как unsigned char и преобразованный в int
    int len = strlen(arguments);
    arguments[len-1] = 0;                       // убираем /n
    len--;                                      // убираем /n
    //int cmd_num = 1;
    printf("str=[%s], [%d]\n", arguments, len); 
    for (int i = 1; i < len; i++)
    {
        if (arguments[i] == '|')                 //заменяем '|' на ноль, то есть конец строки
            {         
                arguments[i] = 0;
                //cmd_num += 1;
            }
    }

    parse_cmd(arguments);                        //разделим по пробелам команду на название команды и аргументы 

    for (int i = 1; i < len; i++) 
    {
        if (arguments[i] == 0)
        {
            char* cmd = arguments + i + 1;       //ставим указатель на следующую после нуля позицию(т.е. на начало следующей команды)  
            parse_cmd(cmd);                                    
        }      
    }        
}
    
    
    
 










