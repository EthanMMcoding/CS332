#include <stdio.h>
#include "file_struct.h"
#include "word_counter.h"

int main(int argc, char **argv){

  // file **file_arr = (file**)malloc(sizeof(struct file*));


  // size_t num_files = traverse(argv[1], file_arr);

  // for(int i = 0; i < num_files; i++){
  //   file curr_file = *(*file_arr + i);
  //   FILE *fp = fopen(curr_file.file_name, "r");
  //   if(fp == NULL){
  //     printf("Opening file: %s failed.", curr_file.file_name);
  //     exit(-1);
  //   }



  //   fork();
  //   printf("File Name: %s, File size: %lu, ")
  // }

  FILE *fp = fopen("sample_file", "r");

  int x = word_counter3(fp);

  printf("word count: %d\n", x);
  
  return 0;
}