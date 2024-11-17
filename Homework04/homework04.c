#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>

void *gen_nums(void *index){
  for(int i = 0; i < 500; i++){
    int num = rand() % 1001;
  }
  return NULL;
}

int main(int argc, char **argv){
  pid_t pid;
  int status;
  int fdin, fdout;
  int pipefd[2]; // pipefd[0] is for reading, pipefd[1] for writing

  if(argc < 2){
    printf("Usage: %s <command> [args]\n", argv[0]);
    exit(-1);
  }

  if(pipe(pipefd) == 0){
    if((pid = fork()) == 0){
      close(pipefd[1]);
    }
    else if(pid > 0){
      close(pipefd[0]);
      pthread_t pthids[3]; /* parent thread ids */
      for(int i = 0; i < 3; i++){
        pthread_create(&pthids[i], NULL, gen_nums, (void*)&i);
      }
    }
  }
}