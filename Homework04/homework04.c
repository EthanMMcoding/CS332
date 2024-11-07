#include <stdio.h>
#include <fcntl.h>

int main(int argc, int **argv){
  pid_t pid;
  int status;
  int fdin, fdout;

  if(argc < 2){
    printf("Usage: %s <command> [args]\n", argv[0]);
    exit(-1);
  }
}