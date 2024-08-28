#ifndef INDEX_SUM
#define INDEX_SUM

#include <stddef.h>
#include <stdio.h>

int UABIndexSum(int* arr, size_t size){
  int sum = 0;
  for(int i = 0; i < size; i++){
    printf("The value at index %d is: %d\n", i, arr[i]);
    if(arr[i] == i){
      sum += arr[i];
    }
  }
  return sum;
}

#endif