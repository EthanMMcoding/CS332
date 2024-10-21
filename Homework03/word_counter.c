#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int word_counter(FILE *fp){
  int word = 0;
  int word_count = 0;
  char c;
  char c_copy = '\0';
  while((c = getc(fp)) != EOF){
    c_copy = c;
    if(c != '\n' && c != ' '){
      word = 1;
    }
    if((c == '\n' || c == ' ') && word == 1){
      word_count++;
      word = 0;
    }
  }
  if(c_copy != '\n' && c_copy != ' ' && c_copy != '\0'){
    word_count++;
  }
  return word_count;
}
