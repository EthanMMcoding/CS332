#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>

int main(int argc, char** argv){
  pid_t pid;
  FILE *fp;
  char *line = (char *)malloc(sizeof(char)*BUFSIZ);
  char **lines = (char **)malloc(sizeof(char*)*BUFSIZ);
  char **args = (char **)malloc(sizeof(char*)*BUFSIZ);
  int status;
  time_t start_time, end_time;
  int lines_looper = 0;
  int num_forks = 0;

  if(argc < 2){
    printf("Usage: %s <filename>\n", argv[0]);
    exit(-1);
  }

  fp = fopen(argv[1], "r");
  if(fp == NULL){
    perror("Error opening file");
		printf("Error opening file %s\n", argv[1]);
		exit(-1);
	}

  int e = 0;
  while(fgets(line, BUFSIZ, fp) != NULL){
    line[strlen(line) - 1] = 0;
    lines[e++] = line;
    printf("\n");
    printf("The content in lines[%d]: %s\n", e-1, lines[e-1]);
    printf("\n");

    char *line_copy = (char *)malloc(sizeof(char)*BUFSIZ);
    strcpy(line_copy, line);

    char *token = strtok(line_copy, " ");
    if(token == NULL){
      printf("failed to copy into token");
      exit(-1);
    }

    printf("\n");
    printf("The content in lines[%d] after strtok: %s\n", e-1, lines[e-1]);
    printf("\n");

    int i = 0;
    while(token != NULL){
      args[i++] = token;
      token = strtok(NULL, " ");
    }
    args[i] = NULL;

    start_time = time(NULL);
    time_t *start_time_ptr = &start_time;

    pid = fork();
    num_forks++;

    if(pid == 0){
      for(int x = 0; x < i; x++){
        printf("args[%d]: %s\n", x, args[x]);
      }
      execvp(args[0], args);
      printf("If you see this statement then execvp failed ;-(\n");
      perror("execvp");
      exit(-1);
    }
    else if(pid > 0){
      wait(&status);
        if(WIFEXITED(status)){
          printf("Child process exited with status = %d\n", WEXITSTATUS(status));
        }
        else{
          printf("Child process did not terminate normally!\n");
        }
      end_time = time(NULL);
      time_t *end_time_ptr = &end_time;
      if(num_forks == 1){
        FILE *output_log = fopen("output.log", "w");
        if(output_log == NULL){
          printf("Error opening output.log\n");
          exit(-1);
        }
        fprintf(output_log, "%s\t%s\t%s\n", lines[lines_looper++], ctime(start_time_ptr), ctime(end_time_ptr));
        fclose(output_log);
      }
      else{
        FILE *output_log = fopen("output.log", "a");
        if(output_log == NULL){
          printf("Error opening output.log\n");
          exit(-1);
        }
        fprintf(output_log, "%s\t%s\t%s\n", lines[lines_looper++], ctime(start_time_ptr), ctime(end_time_ptr));
        fclose(output_log);
      }
    } 
    else{
      perror("fork");
      exit(EXIT_FAILURE);
    }
  }

  printf("[%ld]: Exiting program .....\n", (long)getpid());
  fclose(fp);

  return 0;
}