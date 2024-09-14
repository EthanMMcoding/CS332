/* compile with gcc -o str_sort insertion_sort_lab3.c */
#include <stdio.h>  
#include <string.h>
#include <stdlib.h>

int arr_size(){
  int arr_size;
  printf("Enter the size of the array: \n");
  scanf("%d", &arr_size);
  return arr_size;
}

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

char **read_input_str(int size){
  char **arr = malloc(size * sizeof(char*));
  for(int i = 0; i < size; i++){
    int count;
    while ((getchar()) != '\n');
    printf("Enter the string: \n");
    scanf("%n", &count);
    arr[i] = malloc((count+1) * sizeof(char));
    scanf("%s", arr[i]);
  }
  return arr;
}

void display_strs(char **arr, int str_arr_size){
  printf("[");
  for(int i = 0; i < str_arr_size - 1; i++){
    printf("%s, ", arr[i]);
  }
  printf("%s]\n", arr[str_arr_size-1]);
}
 
int main(int argc, char** argv) {

  int size = arr_size();

  char **new_str = read_input_str(size);

  display_strs(new_str, size);

  insertion_sort_str(new_str, size);

  display_strs(new_str, size);

  return 0;  
} 