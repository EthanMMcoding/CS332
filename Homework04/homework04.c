#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int rand_ints[1500];
int rand_ints_test[10];

void *gen_nums(void *index);

void *gen_nums_test(void *index);

int main(int argc, char **argv){
  pid_t pid;
  int status;
  int fdin, fdout;
  int pipefd[2]; /* pipefd[0] is for reading, pipefd[1] for writing */
  pthread_t tid[3];
  long i;

  if(argc > 1){
    printf("Usage: %s\n", argv[0]);
    exit(-1);
  }

  for(i = 0; i < 3; i++){
    pthread_create(&tid[i], NULL, gen_nums, (void*)&i);
  }

  for(i = 0; i < 3; i++){
    pthread_join(tid[i], NULL);
  }

  for(i = 0; i < 1500; i++){
    printf("rand_ints[%ld]: %d\n", i, rand_ints[i]);
  }

  if(pipe(pipefd) == 0){
    if((pid = fork()) == 0){
      close(pipefd[1]); /* close child for writing to pipe */
    }
    else if(pid > 0){
      close(pipefd[0]); /* close parent to reading from pipe */
      pthread_t pthids[3]; /* parent thread ids */
      for(int i = 0; i < 3; i++){
        pthread_create(&pthids[i], NULL, gen_nums, (void*)&i);
      }
      for(int i = 0; i < 3; i++){
        pthread_join(pthids[i], NULL);
      }
      fprintf()
    }
  }
  return 0;
}

void *gen_nums(void *index){
  int my_start, my_end;

  my_start = *(int*)index * 500;
  my_end = my_start + 500;
  if(*(int*)index == (3-1)) my_end = 1500;

  for(int i = 0; i < my_end; i++){
    pthread_mutex_lock(&mutex);
    int num = rand() % 1001;
    pthread_mutex_unlock(&mutex);
    rand_ints[i] = num;
  }

  return NULL;
}


void *gen_nums_test(void *index){

  pthread_mutex_lock(&mutex);
  int num = rand() % 1001;
  pthread_mutex_unlock(&mutex);
  rand_ints_test[*(int*)(index)] = num;

  return NULL;
}