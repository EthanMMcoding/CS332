/* compile with gcc -o homework_01 ethanmm_HW01.c -lm */

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>

int countVowels(char* s){
  int result = 0;
  char vowels['z' + 1] = {
    ['A'] = 'A',
    ['E'] = 'E',
    ['I'] = 'I',
    ['O'] = 'O',
    ['U'] = 'U',
    ['a'] = 'a',
    ['e'] = 'e',
    ['i'] = 'i',
    ['o'] = 'o',
    ['u'] = 'u'
  };
  int i = 0;
  while(s[i]){       // count on null terminator to end the loop
    if(vowels[s[i]]){
      result += 1;
    }
    i++;
  }
  return result;
}

bool evenSquare(int n){
  int sqrt_n = (int)sqrt(n);
  if(sqrt_n%2 == 0 && sqrt_n*sqrt_n == n){
    return true;
  }
  else{
    return false;
  }
}

int* replaceEvenWithZero(int* arr, int size){
  static int* new_arr;
  new_arr = (int*)malloc(size * sizeof(int));
  for(int i = 0; i < size; i++){
    if(arr[i]%2 == 0){
      new_arr[i] = 0;
    }
    else{
      new_arr[i] = arr[i];
    }
  }
  return new_arr;
}

int UABIndexSum(int* arr, int size){
  int sum = 0;
  for(int i = 0; i < size; i++){
    if(i == arr[i]){
      sum += arr[i];
    }
  }
  return sum;
}


int factorial(int n){
  if(n == 0 || n == 1){
    return 1;
  }
  else{
    return(n * factorial(n-1));
  }
}

bool isPrime(int n){
  int x_sqrt = (int)sqrt(n);
  if(n%2 == 0 || n <= 1){
    if(n == 2){
      return true;
    }
    return false;
  }
  for(int i = 3; i <= x_sqrt; i+=2){
    if(n%i == 0){
      return false;
    }
  }
  return true;
}

char* primeOrFactorial(int n){
  if(n <= 1){
    return "Invalid Input";
  }
  else if(isPrime(n)){
    return "Prime Number";
  }
  else{
    int factorial_n = factorial(n);
    int length = snprintf(NULL, 0, "%d", factorial_n);      // To convert this integer to char array, I used the snprintf function passed with NULL to get the size
    char* str_factorial = malloc(length+1);                 // Used malloc to allocate space for the char array
    snprintf(str_factorial, length+1, "%d", factorial_n);   // Finally wrote the integer into the char array
    return str_factorial;
  }
}

int main(){

  /* primeOrFactorial tests */
  printf("\n");
  printf("---Beginning of PrimeOrFactorial testing---\n");
  int prime_or_factorial_arr[] = {5, 4, 1, 7, -3};
  int prime_or_factorial_size = sizeof(prime_or_factorial_arr)/sizeof(prime_or_factorial_arr[0]);
  for(int i = 0; i < prime_or_factorial_size; i++){
    printf("Prime or Factorial of: %d %s\n", prime_or_factorial_arr[i], primeOrFactorial(prime_or_factorial_arr[i]));
  }

  /* UABIndexSum testing */
  printf("\n");
  printf("---Beginning of UABIndexSum testing---\n");
  int UAB_index_sum_arrs[3][4] = {
    {0, 2, 2, 4}, 
    {3, 1, 0, 4}, // the expected output on the hw1 pdf is wrong, [1][1] is equal to 1, therefore result += 1
    {1, 2, 3, 3}
};
  int index_arr_size = sizeof(UAB_index_sum_arrs)/sizeof(UAB_index_sum_arrs[0]);        // size of outer array
  int index_arr_sizes = sizeof(UAB_index_sum_arrs[0])/sizeof(UAB_index_sum_arrs[0][1]); // size of arrays within the array
  for(int i = 0; i < index_arr_size; i++){
    printf("The sum of all elements that are equal to their indices in array %d is: %d\n", i, UABIndexSum(UAB_index_sum_arrs[i], index_arr_sizes));
  }

  /* replaceEvenWithZero testing */
  printf("\n");
  printf("---Beginning of replaceEvenWithZero testing---\n");
  int replace_with_zero_arr[3][4] = {
    {1, 2, 3, 4},
    {2, 4, 6},
    {1, 3, 5}
  };
  int replace_with_zero_arr1[] = {1, 2, 3, 4};
  int replace_with_zero_arr2[] = {2, 4, 6};
  int replace_with_zero_arr3[] = {1, 3, 5};
  
  int* new_arr1 = replaceEvenWithZero(replace_with_zero_arr1, 4);
  int* new_arr2 = replaceEvenWithZero(replace_with_zero_arr2, 3);
  int* new_arr3 = replaceEvenWithZero(replace_with_zero_arr3, 3);
  for(int i = 0; i < 4; i++){
    printf("The value at index: %d of new_arr1 is: %d\n", i, new_arr1[i]);
  }
  printf("\n");
  for(int i = 0; i < 3; i++){
    printf("The value at index: %d of new_arr2 is: %d\n", i, new_arr2[i]);
  }
  printf("\n");
  for(int i = 0; i < 3; i++){
    printf("The value at index: %d of new_arr3 is: %d\n", i, new_arr3[i]);
  }
  printf("\n");

  /* evenSquare testing */
  printf("\n");
  printf("---Beginning of evenSquare testing---\n");
  int even_square_arr[] = {16, 15, 25, 36};
  int even_square_arr_size = sizeof(even_square_arr)/sizeof(even_square_arr[0]);

  for(int i = 0; i < even_square_arr_size; i++){
    printf("The number %d is %s\n", even_square_arr[i], evenSquare(even_square_arr[i]) ? "an even square(True)":"not an even square(False)");
  }

  printf("\n");
  printf("---Beginning of countVowels testign\n");
  char strings[4][12] = { 
    "Hello World", 
    "UAB CS", 
    "Python", 
    "aeiou"
  };
  int strings_size = sizeof(strings)/sizeof(strings[0]);

  for(int i = 0; i < strings_size; i++){
    printf("The number of vowels in string: %s is: %d\n", strings[i], countVowels(strings[i]));
  }
  return 0;
}

// compiled with gcc -o homework_01 ethanmm_HW01.c -lm