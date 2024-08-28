#include <stdio.h>
#include <stdbool.h>
#include "prime_or_factorial.h"
#include "index_sum.h"

int main(){

  int arr[] = {0, 1, 2, 3, 4};
  size_t size = sizeof(arr)/sizeof(int);
  printf("%lu\n", size);
  printf("The sum of all elements that are equal to their indices is: %d\n", UABIndexSum(arr, size));
  printf("%s\n", primeOrFactorial(4));

  return 0;
}