#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "file_struct.h"
#include "word_counter.h"
#include "traverse.h"

int main(int argc, char **argv){
  pid_t pid;
  int status;
  int i = 0;
  int x = 0;

  if (argc != 2) {
    printf("Usage: %s <command> [args]\n", argv[0]);
    exit(-1);
  }

  file **file_arr = (file**)malloc(sizeof(struct file*));

  size_t num_files = traverse(argv[1], file_arr);

  pid_t *pid_arr = (pid_t*)malloc(sizeof(pid_t) * num_files);

  int count = 0;
  pid = fork();
  printf("count: %d\n", ++count);

  while(pid == 0){
    FILE *fp;
    int word_count = 0;

    if(i < num_files){
      file cur_file = *(*file_arr + i);
      char *parent_path = cur_file.parent_dir_path;
      char *file_name = cur_file.file_name;
      int file_size = cur_file.file_stat.st_size;
      int file_level = cur_file.level;

      if(file_level > 0 && strstr(file_name, ".txt")){
        char *file_path = (char*)malloc(sizeof(char) * BUFSIZ);
        snprintf(file_path, BUFSIZ, "%s/%s", parent_path, file_name);
        fp = fopen(file_path, "r");
        word_count = word_counter(fp);
        fclose(fp);
        printf("File name: %s, File size: %d, Word count: %d\n", file_name, file_size, word_count);
      }
      else if(file_level > 0 && !strstr(file_name, ".txt")){
        char *file_path = (char*)malloc(sizeof(char) * BUFSIZ);
        snprintf(file_path, BUFSIZ, "%s/%s", parent_path, file_name);
        printf("File name: %s, File size: %d\n", file_name, file_size);
      }
      else if(file_level == 0 && strstr(file_name, ".txt")){
        fp = fopen(file_name, "r");
        word_count = word_counter(fp);
        fclose(fp);
        printf("File name: %s, File size: %d, Word count: %d\n", file_name, file_size, word_count);
      }
      else{
        printf("File name: %s, File size: %d\n", file_name, file_size);
      }
    }
    i++;
    if(i >= num_files){
      for(int j = 0; j < num_files; j++){
        printf("pid_arr[%d]: %d\n", j, pid_arr[j]);
      }
      exit(1);
    }
    pid = fork(); /* fork is called once and returns twice, only called repeatedly in the children */
    pid_arr[x++] = getpid();
    printf("Parent id: %d Current id: %d\n", getppid(), getpid());
  }
  if(pid > 0){
      wait(&status);
        if(WIFEXITED(status)){
          printf("Child process exited with status = %d\n", WEXITSTATUS(status));
        }
        else{
          printf("Child process did not terminate normally!\n");
        }
    }
    else {
      perror("fork");
      exit(EXIT_FAILURE);
    }
  
  return 0;
}