

struct sembuf Sem_v = {.sem_num = 0, .sem_op = +1, .sem_flg = 0};
struct sembuf Sem_p = {.sem_num = 0, .sem_op = -1, .sem_flg = 0};
//=========================================================
static const unsigned Process_num = 20;
static const unsigned Incr_num    = 500000;
//=========================================================
static int child(int sem_id, int* value, unsigned incr_num);
//=========================================================

static int child(int sem_id, int* value, unsigned incr_num)
{
    // int local_val = 0;

    // for (unsigned j = 0; j < incr_num; j++)
    // {
    //     local_val += 1;
    // }

    struct sembuf op = Sem_p;
    op.sem_flg |= SEM_UNDO;

    int err = semop(sem_id, &op, 1);
    *value += local_val;

    // There is no point of detaching shared memory in child process

    return 0;
}

//---------------------------------------------------------

int main()
{
    int shm_id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | IPC_EXCL | 0700);
    int* value = shmat(shm_id, NULL, 0);
    int sem_id = semget(IPC_PRIVATE, 1, IPC_CREAT | IPC_EXCL | 0700);
    int err = semop(sem_id, &Sem_v, 1);
    *value = 0;
    pid_t pid = 0;
    for (unsigned iter = 0; iter < Process_num; iter++)
    {
        pid = fork();
        if (pid == 0)
        {
            return child(sem_id, value, Incr_num);
        }
        else
            continue;
    }

    for (unsigned iter = 0; iter < Process_num; iter++)
    {
        pid_t term = wait(NULL);
        
    }

   }


    printf("Total value: %d \n", *value);
    err = semctl(sem_id, 1, IPC_RMID);
    err = shmdt(value);
    err = shmctl(shm_id, IPC_RMID, NULL);
    
}