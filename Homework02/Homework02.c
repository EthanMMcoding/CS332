#define _XOPEN_SOURCE >= 700

#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

void print_stat(struct stat statbuf){
  printf("file type:          ");

  switch (statbuf.st_mode & S_IFMT){
  case S_IFREG: printf("regular\n");   break;
  case S_IFDIR: printf("directory\n"); break;
  case S_IFCHR: printf("character\n"); break;
  case S_IFBLK: printf("block\n");     break;
  case S_IFIFO: printf("FIFO/pipe\n"); break;
  case S_IFLNK: printf("symlink\n");   break;
  case S_IFSOCK: printf("socket\n");   break;
  default :
    printf("unkown?\n");
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