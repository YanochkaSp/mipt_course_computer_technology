#include <unistd.h>
#include <stdio.h>
#include <sys/types.h> 
#include <sys/wait.h>

int main(int argc, char *argv[]) 
{
    pid_t pid_1 = fork();
    if (pid_1 == 0)
    {
        printf("h\n");
    }
    else
    {
        wait(NULL);
    }

    pid_t pid_2 = fork();
    if (pid_2 == 0)
    {
        printf("e\n");
    }
    else
    {
        wait(NULL);
    }

    pid_t pid_3 = fork();
    if (pid_3 == 0)
    {
        printf("l\n");
    }
    else
    {
        wait(NULL);
    }

    pid_t pid_4 = fork();
    if (pid_4 == 0)
    {
        printf("l\n");
    }
    else
    {
        wait(NULL);
    }    

    pid_t pid_5 = fork();
    if (pid_5 == 0)
    {
        printf("o\n");
    }
    else
    {
        wait(NULL);
    }
    // for (int i = 1; i < 11; i++)
    // {
        
    //     printf("h\n");
    //     if (pid == 0)
    //     {
    //         printf("h\n");
    //     }
    //     else 
    //     {
    //         wait(NULL);
    //     }
    // }
}