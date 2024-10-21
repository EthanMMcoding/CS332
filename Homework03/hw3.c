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

  if (argc != 2) {
    printf("Usage: %s <command> [args]\n", argv[0]);
    exit(-1);
  }

  file **file_arr = (file**)malloc(sizeof(struct file*));


  size_t num_files = traverse(argv[1], file_arr);

  pid = fork();

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
      exit(1);
    }
    pid = fork();
    printf("%d\n", i);
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

  // for(int i = 0; i < num_files; i++){
  //   file curr_file = *(*file_arr + i);
  //   char *file_name = curr_file.file_name;

  //   pid = fork();

  //   if(pid == 0){
  //   FILE *fp;
  //   if(curr_file.level > 0){
  //     char *file_path = (char*)malloc(sizeof(char) * BUFSIZ);
  //     snprintf(file_path, BUFSIZ, "%s/%s", curr_file.parent_dir_path, curr_file.file_name);
  //     printf("file path: %s\n", file_path);
  //     printf("\nYo %s\n\n", file_path);
  //     fp = fopen(file_path, "r");
  //     if(fp == NULL){
  //       printf("Opening file: %s failed.\n", file_name);
  //       exit(-1);
  //     }
  //   }
  //   else{
  //     fp = fopen(file_name, "r");
  //     if(fp == NULL){
  //       printf("Opening file: %s failed.\n", file_name);
  //       exit(-1);
  //     }
  //   }
  //     if(strstr(file_name, ".txt")){
  //       int word_count = word_counter(fp);
  //       printf("File Name: %s, File size: %lu, Word count: %d\n", file_name, curr_file.file_stat.st_size, word_count);
  //     }
  //     else{
  //       printf("File Name: %s, File size: %lu\n", file_name, curr_file.file_stat.st_size);
  //     }
  //     fclose(fp);
  //   }
  // }

  // FILE *fp = fopen("sample_file", "r");

  // int x = word_counter(fp);

  // printf("word count: %d\n", x);
  
  return 0;
}