#ifndef PRIME_OR_FACTORIAL
#define PRIME_OR_FACTORIAL

#include <stdbool.h>
#include <math.h>
#include <stdio.h>

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

char* prime_or_factorial(int n){
  if(n <= 1){
    return "Invalid Input";
  }
  else if(is_prime(n)){
    return "Prime Number";
  }
  else{
    int factorial_n = factorial(n);
    int length_of_factorial = snprintf(NULL, 0, "%d", factorial_n);
    char str_factorial[length_of_factorial+1];
    snprintf(str_factorial, length_of_factorial, "%d", factorial_n);
    return str_factorial; // need to convert this to string
  }
}

#endif