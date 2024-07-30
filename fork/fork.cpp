//fork разделяет процесс на 2 процесса

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
int main() {
    pid_t pid, ppid, chpid;
    int a = 1;
    // pid = getpid();
    // printf("My pid = %d, my ppid = %d, chpid = %d\n",pid, ppid, chpid);
    for (int i = 1; i < 3; i++) {     
        chpid = fork();

        printf("chpid = %d\n",chpid);
    }

}