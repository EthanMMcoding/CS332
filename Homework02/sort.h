#ifndef SORT

#include <string.h>

void insertion_sort_str(char **arr, int size){
  for(int i = 0; i < size; i++){
    char *key = arr[i];
    int j = i - 1;
    while(j >= 0 && strcmp(arr[j], key) > 0){
      arr[j + 1] = arr[j];
      j -= 1;
    }
    arr[j + 1] = key;
  }
}

#endif