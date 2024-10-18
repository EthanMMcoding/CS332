#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

// word here and here and here
// and here and here
//   here 
//   now here too

int word_counter(FILE *fp){
  size_t max_len = BUFSIZ;
  int word_count = 0;
  char *word = NULL;
  while(getdelim(&word, &max_len, ' ', fp) != -1){
    int word_len = strlen(word);
    word[word_len-1] = '\0';
    // printf("%d ", )
    int i = 0;
    while(word[i]){
      printf("%d ", word[i]);
      i++;
    }
    printf("\n");
    if(word[0] != ' ' && word[0] != '\n'){
      word_count++;
    }
    if(word[0] != ' ' && word[0] != '\n' && (strchr(word, 32) || strchr(word, 10))){
      word_count++;
    }
    printf("Word number: %d, Word: %s\n", word_count, word);
    printf("\n");
  }
  return word_count;
}

/* the problem with the current version is that since it delimits by a space,
   it will not separate words that are only split by a newline*/

int word_counter2(FILE *fp){
  int word_count = 0;
  int x = 0;
  char *line = (char*)malloc(sizeof(char) * BUFSIZ);
  char *line_copy = (char*)malloc(sizeof(char) * BUFSIZ);
  char **words = (char**)malloc(sizeof(char*) * BUFSIZ);
  while(fgets(line, BUFSIZ, fp)){
    strcpy(line_copy, line);
    char *token = strtok(line_copy, " ");
    if(token == NULL){
      printf("failed to copy into token");
      exit(-1);
    }
    while(token != NULL){
      words[x++] = token;
      token = strtok(NULL, " ");
    }
  }
  for(int i = 0; i < x; i++){
    printf("word %d: %s\n", i, words[i]);
  }
  return word_count;
}

int word_counter3(FILE *fp){
  int word = 0;
  int word_count = 0;
  char c;
  char c_copy;
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
  if(c_copy != '\n' && c_copy != ' '){
    word_count++;
  }
  return word_count;
}