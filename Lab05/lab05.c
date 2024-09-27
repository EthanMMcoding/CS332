#define _DEFAULT_SOURCE /* specifying the BSD features I am using (the DT_ macros) */

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

char *filetype(unsigned char type) {
  char *str;
  switch(type) {
  case DT_BLK: str = "block device"; break;
  case DT_CHR: str = "character device"; break;
  case DT_DIR: str = "directory"; break;
  case DT_FIFO: str = "named pipe (FIFO)"; break;
  case DT_LNK: str = "symbolic link"; break;
  case DT_REG: str = "regular file"; break;
  case DT_SOCK: str = "UNIX domain socket"; break;
  case DT_UNKNOWN: str = "unknown file type"; break;
  default: str = "UNKNOWN";
  }
  return str;
}

void traverse(const char *arg){
  DIR *parentDir = opendir(arg);
  if (parentDir == NULL) { 
    printf ("Error opening directory '%s'\n", arg); 
    exit (-1);
  }
  struct dirent *dirent;
  int count = 1;
  static int level = 0;
  while((dirent = readdir(parentDir)) != NULL){ 
    if(strcmp(dirent->d_name, ".") == 0 || strcmp(dirent->d_name, "..") == 0){
      continue;
    }
    if(strcmp(filetype(dirent->d_type), "directory") != 0){
      for(int i = 0; i < level; i++){
        printf("    ");
      }
      printf ("[%d] %s (%s)\n", count, dirent->d_name, filetype(dirent->d_type)); 
    }
    else{
      for(int i = 0; i < level; i++){
        printf("    ");
      }
      level++;
      printf ("[%d] %s (%s)\n", count, dirent->d_name, filetype(dirent->d_type));
      char path[PATH_MAX] = {0};
      strcat(path, arg); strcat(path, "/"); strcat(path, dirent->d_name);
      traverse(path);
    }
    count++; 
  }
  level--;
  closedir (parentDir);
}

int main (int argc, char **argv) {  

  if (argc < 2) { 
    printf ("Usage: %s <dirname>\n", argv[0]); 
    exit(-1);
  }
  traverse (argv[1]);
}