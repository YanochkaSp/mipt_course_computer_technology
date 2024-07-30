#include <unistd.h>
#include <stdio.h>  
#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/types.h>

/* системный вызов semop берет массив отсюда. */
static const struct sembuf Sem_p = {
    .sem_num = 0,        /* индекс семафора в массиве */
    .sem_op  = -1,       /* операция */
    .sem_flg = 0,        /* флаги */
};

static const struct sembuf Sem_v = {
    .sem_num = 0,
    .sem_op  = +1,   
    .sem_flg = 0
};

void child_process(int sem_id, int *p) 
{

    int local_counter = 0;

    for (unsigned k = 0; k < 1000000; k++) 
    {
        local_counter++;
    }  

    semop(sem_id, &Sem_p, 1);
    *p += local_counter;
    semop(sem_id, &Sem_v, 1);
}

int main(int argc, char *argv[]) {   

    int shm_id = shmget(IPC_PRIVATE, 4096,  IPC_CREAT | IPC_EXCL | 0666);  //create a block of shared memory associated with key, returns the ID of the block
    
    int* value = shmat(shm_id, NULL, 0);           //map the block into this processes adress space, returns a pointer to that blocks, we can atually start using a memory
    int sem_id = semget(IPC_PRIVATE, 1, IPC_CREAT | IPC_EXCL | 0666);//semget не выполняется, если semflg имеет флаги IPC_CREAT и IPC_EXCL, а набор семафоров уже существует для key.
        
    *value = 0;

    for (int i = 0; i < 10; i++) 
    {
        pid_t pid = fork();

        if (pid == 0) {
            child_process(sem_id, value);
            exit(0);            // Тоже, что и exit(EXIT_SUCCESS)
        }
    }  

    for (int i = 0; i < 10; i++) {
        wait(NULL);
    }

    printf("%d\n", *value);

    semctl(sem_id, 1, IPC_RMID);
    shmctl(shm_id, IPC_RMID, 0);      //destroy a memory block; IPC_RMID-remove this block based on this id
}