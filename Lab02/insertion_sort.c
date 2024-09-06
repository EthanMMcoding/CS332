/* compile with gcc -o sort insertion_sort.c */

#include <stdio.h>

void insertion_sort(int arr[], int size){
  for(int i = 1; i < size; i++){
    int key = arr[i];
    int j = i - 1;
    while(j >= 0 && arr[j] > key){
      arr[j + 1] = arr[j];
      j -= 1;
    }
    arr[j + 1] = key;
  }
}

int main(){

  int size = 0;

  printf("\n");
  printf("This program will first ask you to input the number that will be\n");
  printf("the size of the array. After inputting a valid array size (>0),\n");
  printf("you will be asked to input each individual element of the array\n");
  printf("one at a time. When the array is full, it will be sorted with\n");
  printf("insertion sort.\n");
  printf("\n");
  
  printf("Input the size of your array: ");
  scanf("%d", &size);
  printf("\n");

  if(size <= 0){
    printf("Array size can not be <= 0.\n");
    return -1;
  }

  int arr[size];

  for(int i = 0; i < size; i++){
    printf("Input an element into your array until the array is full: ");
    scanf("%d", &arr[i]);
    printf("\n");
  }
  
  insertion_sort(arr, size);

  for(int i = 0; i < size; i++){
    printf("%d\n", arr[i]);
  }
  return 0;
}