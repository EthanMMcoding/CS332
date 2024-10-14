/* compile with gcc -o hw2 Homework02.c*/
#define _XOPEN_SOURCE 700
#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "traverse.h"
#include "sort.h"
#include "file_struct.h"

int main(int argc, char **argv){

  /* remember, a pointer to a pointer in this case is just a pointer to a pointer to 
  an allocated portion of memory, the pointer being pointed to points to the 
  beginning of this allocated portion, pointer arithmetic allows access to the 
  elements past the first one*/

  file **file_arr = malloc(sizeof(struct file*));

  if(argc == 1){
    size_t arr_count = traverse(".", file_arr);
    for(int i = 0; i < arr_count; i++){
      file curr_file = *(*file_arr + i);
      for(int j = 0; j < curr_file.level; j++){
        printf("\t");
      }
      printf("%s\n", curr_file.file_name);
    }
    return 0;
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

  if(!opt_arr[0] && !opt_arr[1] && !opt_arr[2] && !opt_arr[3]){
    size_t arr_count = traverse(".", file_arr);
    for(int i = 0; i < arr_count; i++){
      file curr_file = *(*file_arr + i);
      for(int j = 0; j < curr_file.level; j++){
        printf("\t");
      }
      printf("%s\n", curr_file.file_name);
    }
    return 0;
  }

  if(file_arr == NULL) {
    printf("Error allocating memory for stat_arr\n");
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
    sort(*file_arr, arr_count);
    for(int i = 0; i < arr_count; i++){
      file curr_file = (*(*file_arr + i));
      if(curr_file.filtered){
        continue;
      }
      if(curr_file.sym_linked_file){
        printf("Symbolic link: %s (%s) (%lld)\n", curr_file.file_name, curr_file.sym_linked_file, (long long)curr_file.file_stat.st_size);
      }
      printf("%s (%lld)\n", curr_file.file_name, (long long)curr_file.file_stat.st_size);
    }
  }

  /* just r */
  else if(opt_arr[2]){
    sort(*file_arr, arr_count);
  }
  /* with S */
  else if(opt_arr[0]){
    for(int i = 0; i < arr_count; i++){
      file curr_file = (*(*file_arr + i));
      if(curr_file.filtered){
        continue;
      }
      if(opt_arr[3] || opt_arr[1]){
        int parent_level = curr_file.level - 1;
        if((strstr(curr_file.parent_dir_path, string_pattern) == NULL || file_size_in_bytes > 4096) && curr_file.level > 0){ /* 4096, default size of directories (I hope)*/
          for(int i = 0; i < parent_level; i++){
            printf("\t");
          }
          printf("(filtered directory) %s\n", curr_file.parent_dir_path);
        }
      }
      for(int x = 0; x < curr_file.level; x++){
        printf("\t");
      }
       if(curr_file.sym_linked_file){
        printf("Symbolic link: %s (%s) (%lld)\n", curr_file.file_name, curr_file.sym_linked_file, (long long)curr_file.file_stat.st_size);
      }
      printf("%s (%lld)\n", curr_file.file_name, (long long)curr_file.file_stat.st_size);
    }
  }
  /* if not S */
  if(!opt_arr[0]  && (opt_arr[3] || opt_arr[1])){
    for(int i = 0; i < arr_count; i++){
      file curr_file = (*(*file_arr + i));
      if(curr_file.filtered){
        continue;
      }
      if(opt_arr[2]){
        for(int i = 0; i < arr_count; i++){
          file curr_file = (*(*file_arr + i));
          if(curr_file.filtered){
            continue;
          }
          if(curr_file.sym_linked_file){
            printf("Symbolic link: %s (%s)\n", curr_file.file_name, curr_file.sym_linked_file);
          }
          printf("%s \n", curr_file.file_name);
          printf("%s (%lld)\n", curr_file.file_name, (long long)curr_file.file_stat.st_size);
        }
        break;
      }
      if(opt_arr[3] || opt_arr[1]){
        int parent_level = curr_file.level - 1;
        if((strstr(curr_file.parent_dir_path, string_pattern) == NULL || file_size_in_bytes > 4096) && parent_level > 0){
          for(int i = 0; i < parent_level; i++){
            printf("\t");
          }
          printf("(filtered directory) %s\n", curr_file.parent_dir_path);
        }
        for(int i = 0; i < curr_file.level; i++){
          printf("\t");
        }
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
  free(file_arr);
  return 0;
}