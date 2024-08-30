BlazerID: ethanmm

The functions I created to complete HW01:

  * primeOrFactorial()
  * isPrime()
  * factorial()
  * UABIndexSum()
  * replaceEvenWithZero()
  * evenSquare()
  * countVowels()

Explanations:

  * char* primeOrFactorial(int n), bool isPrime(int n), and int factorial(int n)
      primeOrFactorial() is the function I created to solve the first problem on the 
      homework. To make the function more readable, I created two helper functions called isPrime() and factorial().

      The function isPrime() calculates a prime number by checking if the number is divisible by 2 (with the exclusion of 2, as it is a prime number), or if its less than 1 since negatives can not be a prime number. This function returns a bool value, true if prime, false if not. The sqrt of a number is converted to int to avoid comparing doubles or floats.

      The function factorial() calculates the factorial of a given number by recursively multiplying itself by the next smallest factor until reaching 1 or 0, in which case 1 is returned and recursion is ended. This function returns the integer factorial of a number.

      primeOrFactorial() then uses a series of if statements involving isPrime() and factorial() to satisfy the requirements of the homework. In the else{} block of code in this function, factorial(n) is calculated, but to convert it to string I had to use the snprintf() function, first reading the length of the integer into a variable, then assignining that space on the heap for a char* using malloc, then finally with the second call of snprintf() the value is read into the char* variable which is then returned.

  * int UABIndexSum(int* arr, int size)
      The UABIndexSum function is a for loop with a sum variable, ever pass through the loop the index is compared with the value at its position in the array. If the the index and the value are equal, sum is incremented by the value in the array. Returns sum of all indices that are equal to the value at their position in the array.
    
  * int* replaceEvenWithZero(int* arr, int size)
      This function returns a pointer to new array in which all even numbers are replaced with zero. First a static int* array is declared, static to prevent this new pointer from disappearing from memory when the funcion returns. Then, the static array is assigned sufficient memory space on the heap using malloc casted to int*. Next, a for loop is entered, the for loop has an if{} block checking for evens and replacing them with zero in the new array, and an else{} block keeping the value of the odd numbers in the new array at their correct positions. 

  * bool evenSquare(int n)
      evenSquare returns a bool value, true if the number is an even square, false if the number is not an even square. The square root is calculated and casted to int, then it is checked to see if it is divisible by 2 and if the number multiplied by itself is equal again to the original number passed in. If both are true, true is returned and the number is an even square. If one is false, false is returned and the number is not an even square.

  * int countVowels(char* s)
      This function returns an integer value that represents the number of vowels that a string contains. To do this, I implemented a hash table the size of the ascii value of the lower case letter 'z' + 1. Then I assigned each vowel's ascii value to its corresponding index in the table. Then I looped through the array, checking if a letter existed there, and if it did was it in the vowels table. If it was, increment result counter by 1. When the end of the char array is reached, return the result.


Citations:

  https://stackoverflow.com/questions/8257714/how-can-i-convert-an-int-to-a-string-in-c

  https://stackoverflow.com/questions/10675399/why-cant-the-size-of-a-static-array-be-made-variable

  https://www.tutorialspoint.com/cprogramming/c_return_arrays_from_function.htm

  https://www.asciitable.com/

  https://www.geeksforgeeks.org/strings-in-c/

  https://www.geeksforgeeks.org/array-of-strings-in-c/

  https://leetcode.com/problems/roman-to-integer/solutions/1960876/c-100-hashtable-solution-o-n/
