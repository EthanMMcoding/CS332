#include <stdio.h>  
#include <string.h>

void insertion_sort_str(char **arr, size_t size){
  for(int i = 0; i < size; i++){
    char *key = arr[i];
    int j = i - 1;
    while(j >= 0 && arr[j] > key){
      arr[j + 1] = arr[j];
      j -= 1;
    }
    arr[j + 1] = key;
  }
}
 
int main(int argc, char** argv) {

  /* figuring out the string functions */

  /* 
  
  stackoverflow post: "How do I create an array of strings in C?"
  what does it mean in the answer to this post that string constants may not be writable? 

  */

  char arr[3][6] = 
  {
    "hello", 
    "nice", 
    "bob"   };

  printf("[");
  for(int i = 0; i < 2; i++){
    printf("%s, ", arr[i]);
  }
  printf("%s]\n", arr[2]);

  return 0;  
} 