#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {

  char* program_name = argv[1];         // мы запускаем ./mytime echo hello world и первым в массиве лежит ./mytime, а запускать надо echo

  struct timeval start_program = {};
  gettimeofday(&start_program, NULL);

  pid_t pid = fork();                   //содание дочернего процесса

  if (pid == 0) {
    execvp(program_name, argv+1);
    perror("error exec");
  }

  if (pid != 0) {                       //если родительский процесс
                      
    wait(NULL);    

    struct timeval end_program;
    gettimeofday(&end_program, NULL);

    struct timeval time_program = {};      //Макрос timersub() вычитает значение времени b из a
    timersub(&end_program, &start_program, &time_program);

    printf("seconds : %ld \n micro seconds : %d\n", time_program.tv_sec, time_program.tv_usec);
  }
}
