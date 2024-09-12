#include <stdio.h>  
#include <string.h>

void insertion_sort_str(char **arr, size_t size){
  for(int i = 0; i < size; i++){
    char *key = *(arr + i);
    int j = i - 1;
    while(j >= 0 && strcmp(arr[j], key) > 0){
      *(arr + j + 1) = *(arr + j);
      j -= 1;
    }
    arr[j + 1] = key;
  }
}
 
int main(int argc, char** argv) {

  char *arr[] = {"Z", "b", "dd", "aa" ,"ZZZ", "c", "eee", "YY", "f", "xx", "fff", "DD", "yy", "zz", "B", "CC", "AA", "dd", "x", "EE", "FF", "X", "xx", "AAA", "cc", "Y", "ZZ"};

  size_t arr_size = sizeof(arr)/sizeof(arr[0]);

  printf("The unsorted array is:\n[");
  for(int i = 0; i < arr_size-1; i++){
    printf("%s, ", arr[i]);
  }
  printf("%s]\n", arr[arr_size-1]);

  insertion_sort_str(arr, arr_size);

  printf("[");
  for(int i = 0; i < arr_size-1; i++){
    printf("%s, ", arr[i]);
  }
  printf("%s]\n", arr[arr_size-1]);

  return 0;  
} 