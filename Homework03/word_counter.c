#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

// word here and here and here
// and here and here
//   here 
//   now here too

int word_counter(FILE *fp){
  ssize_t n;
  ssize_t max_len = BUFSIZ;
  int word_count = 0;
  char *word = NULL;
  while((n = getdelim(&word, &max_len, ' ', fp)) > 0){
    // printf("%d\n", word[0]);
    // if(word[0] != ' ' && word[0] != '\n'){
    //   word_count++;
    // }
    word_count++;
  }
  return word_count;
}

// int word_counter(FILE *fp){
//   char c;
//   int word_count;
//   int is_word;
//   while((c = fgetc(fp) != EOF)){
//     if(c == ' ' || c == '\n'){
//       is_word = 0;
//     }
//     else{
//       if(!is_word){
//         word_count++;
//         is_word = 1;
//       }
//     }
//   }
//   return word_count;
// }