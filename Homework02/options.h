#ifndef OPTIONS

#include <stdio.h>
#include <string.h>
#include "file_struct.h"

void S(file *file_arr, size_t size){
  for(int i = 0; i < size; i++){
    file curr_file = *(file_arr + i);
    for(int j = 0; j < curr_file.level; j++){
      printf("\t");
    }
    if((curr_file.file_stat.st_mode & S_IFMT) == S_IFLNK){
      printf("%s is a symbolic link (%s)\n", curr_file.file_name, curr_file.sym_linked_file);  
    }
    else{
      printf("%s (%lld)\n", curr_file.file_name, (long long)curr_file.file_stat.st_size);
    }
  }
}

// void r(file **arr, int size){
//   for(int i = 0; i < size; i++){
//     char *key = arr[i];
//     int j = i - 1;
//     while(j >= 0 && strcmp(arr[j], key) > 0){
//       arr[j + 1] = arr[j];
//       j -= 1;
//     }
//     arr[j + 1] = key;
//   }
// }

void opt_handler();

#endif