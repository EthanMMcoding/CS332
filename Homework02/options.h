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

void s(file *file_arr, size_t size, long long comparison_size){

}

void r(file *file_arr, size_t size){
  for(int i = 1; i < size; i++){
    file file_i = *(file_arr + i);
    long key = file_i.file_stat.st_size;
    int j = i - 1;
    while(j >= 0 && (*(file_arr + j)).file_stat.st_size < key){
      *(file_arr + j + 1) = *(file_arr + j);
      j--;
    }
    *(file_arr + j + 1) = file_i;
  }
}

void opt_handler();

#endif