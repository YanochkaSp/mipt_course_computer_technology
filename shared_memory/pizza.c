#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main(int argc, char* argv[]) {
    int id = semget(,,0);
    semctl(id, IPC_RMID)
}