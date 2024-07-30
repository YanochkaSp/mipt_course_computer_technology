// #include <unistd.h>
// #include <stdio.h>
// #include <sys/types.h> 
// #include <sys/wait.h>
// #include <string.h> 

// int main(int argc, char* argv[])
// {
//     printf("Введите строку: ");
//     char buf[256] = {0};  
//     if (fgets(buf, sizeof(buf), stdin) == NULL) printf("Error with fgets");
//     int len = strlen(buf);
    
//     for (int i = 0; i < len; i++)
//     {
//         pid_t pid = fork();
//         if (pid == -1) return 1;

//         pid_t ppid[100] = {0};
//         ppid[i] = getppid();
//         //printf("%d", ppid[i]);
//         while (ppid[i+1] > ppid[i])
//         {
//             if (pid == 0)
//             {
//                 printf("%c", buf[i]);
//                 break;
//             }
//         }

        

//         sleep(1);
//     }
//     // if (pid != 0)
//     // {
//     //     for (int i = 1; i <= len; i++)
//     //     {
//     //         if (pid[i-1] < pid[i])
//     //         {
                
//     //         }
//     //     }
//     // }
// }

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <string.h> 

int main(int argc, char* argv[])
{
    printf("Введите строку: ");
    char buf[256] = {0};  
    if (fgets(buf, sizeof(buf), stdin) == NULL) printf("Error with fgets");
    int len = strlen(buf);

    for (int i = 0; i < len; i++)
    {
        pid_t pid = fork();
        if (pid == -1) return 1;
        if (pid == 0)
        {
            printf("%c", buf[i]);
            break;
        }
        int status;
        wait(&status);
    }
}