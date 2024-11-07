#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
  FILE *fpin;
  char command[BUFSIZ];
  char buf[BUFSIZ];

  if(argc != 1){
    printf("Usage: %s\n", argv[0]);
    exit(-1);
  }

  printf("Enter command: ");
  fgets(command, sizeof(command), stdin);
  command[strcspn(command, "\n")] = '\0';

  while(strcmp(command, "quit") != 0){

    if((fpin = popen(command, "r")) == NULL ){
      perror("exec");
      exit(-1);
    }

    while(fgets(buf, BUFSIZ, fpin) != NULL) {
      if(fputs(buf, stdout) == EOF) {
        printf("Error writing to pipe\n");
	      exit(EXIT_FAILURE);
      }
    }

    printf("Enter command: ");
    fgets(command, sizeof(command), stdin);
    command[strcspn(command, "\n")] = '\0';
  }

  printf("Exiting program...bye!\n");
  return 0;
}
