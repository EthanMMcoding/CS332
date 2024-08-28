#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>

bool evenSquare(int n){
  int sqrt_n = (int)sqrt(n);
  if(sqrt_n*sqrt_n == n){
    return true;
  }
  else{
    return false;
  }
}

int countVowels(char* s){
  int result = 0;
  char vowels['z' + 1] = {
    ['a'] = 'a',
    ['e'] = 'e',
    ['i'] = 'i',
    ['o'] = 'o',
    ['u'] = 'u'
  };
  int i = 0;
  while(s[i] != 0){
    if(vowels[s[i]]){
      result += 1;
    }
    i++;
  }
  return result;
}

int* replaceEvenWithZero(int* arr, size_t size){
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

int UABIndexSum(int* arr, size_t size){
  int sum = 0;
  for(int i = 0; i < size; i++){
    if(arr[i] == i){
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

bool is_prime(int x){
  double x_sqrt = (int)sqrt(x);
  if(x%2 == 0 || x <= 1){
    if(x == 2){
      return true;
    }
    return false;
  }
  for(int i = 2; i <= x_sqrt; i++){
    if(x%i == 0){
      return false;
    }
  }
  return true;
}

char* primeOrFactorial(int n){
  if(n <= 1){
    return "Invalid Input";
  }
  else if(is_prime(n)){
    return "Prime Number";
  }
  else{
    int factorial_n = factorial(n);
    int length = snprintf(NULL, 0, "%d", factorial_n);
    char* str_factorial = malloc(length+1);
    snprintf(str_factorial, length+1, "%d", factorial_n);
    return str_factorial; // need to convert this to string
  }
}

int main(){

  int arr[] = {0, 1, 2, 3, 4};
  size_t size = sizeof(arr)/sizeof(int);

  int* new_arr = replaceEvenWithZero(arr, size);

  for(int i = 0; i < size; i++){
    printf("The value at index: %d of new_arr is: %d\n", i, new_arr[i]);
  }

  printf("The sum of all elements that are equal to their indices is: %d\n", UABIndexSum(arr, size));

  printf("%s\n", primeOrFactorial(4));

  int number = 4;
  printf("The number %d is %s\n", number, evenSquare(number) ? "an even square":"not an even square");

  printf("The number of vowels in string: %s is: %d\n", "looney tunes", countVowels("looney tunes"));
  return 0;
}