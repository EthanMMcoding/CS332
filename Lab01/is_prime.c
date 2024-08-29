#include <stdio.h>
#include <math.h>

void is_prime(int x){
  double x_sqrt = (int)sqrt(x); // convert from double to int for later comparison in the for loop
  if(x%2 == 0 || x <= 1){
    if(x == 2){
      printf("The given number is prime\n");
      return;
    }
    printf("The given number is not prime\n");
    return;
  }
  for(int i = 3; i <= x_sqrt; i+=2){
    if(x%i == 0){
      printf("The given number is not prime\n");
      return;
    }
  }
  printf("The given number is prime\n");
  return;
}

int main(){

  int user_input = 0;

  printf("Enter a number: ");
	scanf("%d", &user_input);

  is_prime(user_input);

  return 0;
}