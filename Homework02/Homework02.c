#define _XOPEN_SOURCE 700
#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "traverse.h"
#include "sort.h"
#include "file_struct.h"

int main(int argc, char **argv){

  if(argc < 2){
    printf("Usage: %s <dirname>, -s<file size in bytes>, -S, -f<string pattern>, -r\n", argv[0]);
    exit(-1);
  }

  int opt;
  int OPT_NUMBER = 4;
  char **opt_arr = (char**)malloc(sizeof(char*) * OPT_NUMBER);
  char *string_pattern = (char*)malloc(sizeof(char));
  int file_size_in_bytes = 0;

  while((opt = getopt(argc, argv, "Ss:f:r")) != -1) {
    switch(opt){
      case 'S':
        *(opt_arr) = "S";
      break;
      case 's':
        *(opt_arr + 1) = "s";
        if(optarg){
          file_size_in_bytes = atoi(optarg);
        }
        else{
          printf("Usage: -s <file size in bytes>");
        }
      break;
      case 'r':
        *(opt_arr + 2) = "r";
      break;
      case 'f':
        *(opt_arr + 3) = "f";
        if(optarg){
          string_pattern = (char*)malloc((strlen(optarg) + 1) * sizeof(char));
          strcpy(string_pattern, optarg);
        }
        else{
          printf("Usage: -f <string pattern>");
        }
      break;
      case ':':
        printf("option needs a value\n");
       break;
      case '?':
        printf("unknown option: %c\n", optopt);
      break;
    }
  }

  file **file_arr = malloc(sizeof(struct stat*));
  if(file_arr == NULL) {
    printf("Error allocating memory for stat_arr\n");
    exit(-1);
  }

  *file_arr = malloc(sizeof(struct stat));
  if(*file_arr == NULL){
    printf("Error allocating memory for stat_arr1\n");
    free(file_arr);
    exit(-1);
  }

  size_t arr_count = traverse(argv[optind], file_arr);

  /* s */
  if(opt_arr[1]){
    for(int i = 0; i < arr_count; i++){
      if((*(*file_arr + i)).file_stat.st_size < file_size_in_bytes){
        (*(*file_arr + i)).filtered = 1;
      }
    }
  }
  /* f */
  if(opt_arr[3]){
    for(int i = 0; i < arr_count; i++){
      if(strstr((*(*file_arr + i)).file_name, string_pattern) == NULL){
        (*(*file_arr + i)).filtered = 1;
      }
    }
  }
  /* r and S */
  if(opt_arr[2] && opt_arr[0]){
    if(strcmp(opt_arr[2], "r") == 0){
      sort(*file_arr, arr_count);
    }
    for(int i = 0; i < arr_count; i++){
      file curr_file = (*(*file_arr + i));
      if(curr_file.filtered){
        continue;
      }
      printf("%s (%lld)\n", curr_file.file_name, (long long)curr_file.file_stat.st_size);
    }
  }
  /* just r */
  else if(opt_arr[2]){
    sort(*file_arr, arr_count);
  }
  /* just S */
  else if(opt_arr[0]){
    for(int i = 0; i < arr_count; i++){
      file curr_file = (*(*file_arr + i));
      if(curr_file.filtered){
        continue;
      }
      for(int x = 0; x < curr_file.level; x++){
        printf("\t");
      }
      printf("%s (%lld)\n", curr_file.file_name, (long long)curr_file.file_stat.st_size);
    }
  }
  /* if not S */
  if(!opt_arr[0]){
    for(int i = 0; i < arr_count; i++){
      file curr_file = (*(*file_arr + i));
      if(curr_file.filtered){
        continue;
      }
      if(opt_arr[3] || opt_arr[2]){
        printf("%s\n", curr_file.file_name);
      }
      else{
        for(int x = 0; x < curr_file.level; x++){
        printf("\t");
      }
      printf("%s\n", curr_file.file_name);
      }
    }
  }
}