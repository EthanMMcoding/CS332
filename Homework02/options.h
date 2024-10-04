#ifndef OPTIONS

#include <stdio.h>
#include <string.h>
#include "file_struct.h"

void sort(file *file_arr, size_t size){
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

#endif