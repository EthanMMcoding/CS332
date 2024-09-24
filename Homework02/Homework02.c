#define S_IFMT 0170000

#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <linux/stat.h>

void print_stat(struct stat statbuf){
  printf("file type:          ");

  switch (statbuf.st_mode & S_IFMT)
  {
  case S_IFREG:
    break;
  
  default:
    break;
  }
}

int main(int argc, char *argv[]){

  int i;
  struct stat buf;
  char *ptr;

  for(int i = 0; i < argc; i++){
    printf("%s: ", argv[i]);
    if(lstat(argv[i], &buf) < 0){
      printf("lstat error");
      continue;
    }
    if(S_ISREG(buf.st_mode)){
      ptr = "regular";
    }
    else if(S_ISDIR(buf.st_mode)){
      ptr = "directory";
    }
    else if(S_ISCHR(buf.st_mode)){
      ptr = "character special";
    }
    else if(S_ISBLK(buf.st_mode)){
      ptr = "block";
    }
    else if(S_ISFIFO(buf.st_mode)){
      ptr = "fifo";
    }
    else if(S_ISLNK(buf.st_mode)){
      ptr = "link";
    }
    else if(S_ISSOCK(buf.st_mode)){
      ptr = "socket";
    }
    else{
      ptr = "unknown mode";
    }
    printf("%s\n", ptr);
  }
  
  return 0;
}