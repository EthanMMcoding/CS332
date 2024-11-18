#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>

pthread_mutex_t rand_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t write_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t read_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t tot_sum_mutex = PTHREAD_MUTEX_INITIALIZER;

int tot_sum = 0;

void *gen_nums(void *index);
void *read_nums(void *arg);

int main(int argc, char **argv){
  printf("Entered main\n");
  pid_t pid;
  FILE *fp;
  int pipefd[2]; /* pipefd[0] is for reading, pipefd[1] for writing */
  int status;
  int fdin, fdout;
  int i;

  if(argc > 1){
    printf("Usage: %s\n", argv[0]);
    exit(-1);
  }

  if(pipe(pipefd) == 0){
    if((pid = fork()) == 0){
      printf("Entered child process\n");
      close(pipefd[1]); /* close child for writing to pipe */

      pthread_t tid[10];
      fdin = pipefd[0];

      fp = fdopen(fdin, "r");

      for(i = 0; i < 10; i++){
        int pthread = pthread_create(&tid[i], NULL, read_nums, (void *)fp);
        if(pthread == 0){
            continue;
          }
        else{
          perror("pthread_create");
          exit(-1);
        }
      }

      for(i = 0; i < 10; i++){
        pthread_join(tid[i], NULL);
      }

      float average = tot_sum/10;

      FILE *new_output = fopen("average.txt", "w");
      if(new_output == NULL){
        printf("Error opening file %s\n", argv[1]);
        exit(-1);
      }


      if(new_output != NULL) {
        int new_fd = fileno(new_output);
        dup2(1, new_fd);
        printf("The average is: %f\n", average);
        fclose(fp);
      }

    }
    else if(pid > 0){
      printf("Entered parent process\n");
      close(pipefd[0]); /* close parent to reading from pipe */

      pthread_t ptid[3];
      fdout = pipefd[1];

      fp = fdopen(fdout, "w");
      if(fp != NULL){

        for(i = 0; i < 3; i++){
          int pthread = pthread_create(&ptid[i], NULL, gen_nums, (void*)fp);
          if(pthread == 0){
            continue;
          }
          else{
            perror("pthread_create");
            exit(-1);
          }
        }

        for(i = 0; i < 3; i++){
          pthread_join(ptid[i], NULL);
        }
      }
       wait(&status);
        if(WIFEXITED(status)){
          printf("Child process exited with status = %d\n", WEXITSTATUS(status));
        }
        else{
          printf("Child process did not terminate normally!\n");
        }
    }
    else{
      perror("fork");
      exit(-1);
    }
  }
  return 0;
}

void *gen_nums(void *write_fp){
  printf("Entered gen_nums\n");
  int rand_ints[500];

  for(int i = 0; i < 500; i++){
    pthread_mutex_lock(&rand_mutex);
    int num = rand() % 1001;
    rand_ints[i] = num;
    pthread_mutex_unlock(&rand_mutex);
  }
  pthread_mutex_lock(&write_mutex);
  fwrite(&rand_ints, sizeof(int), 500,(FILE *)write_fp);
  pthread_mutex_unlock(&write_mutex);

  return NULL;
}

void *read_nums(void *read_fp){
  printf("Entered read_nums\n");
  int read_ints[150];

  pthread_mutex_lock(&read_mutex);
  fread(&read_ints, sizeof(int), 150, (FILE *)read_fp);
  pthread_mutex_unlock(&read_mutex);

  int partial_sum = 0;
  for(int i = 0; i < 150; i++){
    partial_sum += read_ints[i];
  }

  pthread_mutex_lock(&tot_sum_mutex);
  tot_sum += partial_sum;
  pthread_mutex_unlock(&tot_sum_mutex);

  return NULL;
}