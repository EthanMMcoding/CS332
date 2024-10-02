#ifndef TRAVERSE

#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

size_t traverse(const char *arg, struct stat **stat_arr){
  static size_t arr_count = 0;
  DIR *parentDir = opendir(arg);
  if (parentDir == NULL) { 
    printf("Error opening directory '%s'\n", arg); 
    exit (-1);
  }
  struct dirent *dirent;
  static int level = 0;
  struct stat statbuf;
  while((dirent = readdir(parentDir)) != NULL){
    if(strcmp(dirent->d_name, ".") == 0 || strcmp(dirent->d_name, "..") == 0){
      continue;
    }
    char file_path[PATH_MAX] = {0};
    snprintf(file_path, sizeof(file_path), "%s/%s", arg, dirent->d_name);
    if(lstat(file_path, &statbuf) < 0){
        printf("lstat error on file %s\n", file_path);
      }
    if(!arr_count){
      arr_count++;
      *stat_arr = (struct stat*)malloc(arr_count * sizeof(struct stat));
      if(*stat_arr == NULL){
        printf("Error calling initial malloc");
        exit(-1);
      }
    }
    else{
      arr_count++;
      *stat_arr = realloc(*stat_arr, arr_count * sizeof(struct stat));
      if(*stat_arr == NULL){
        printf("Error reallocating\n");
        exit(-1);
      }
    }
    *(*stat_arr + arr_count - 1) = statbuf;
    if(dirent->d_type == DT_LNK){
      char file_name[FILENAME_MAX];
      readlink(file_path, file_name, FILENAME_MAX);
      stat(file_path, &statbuf);
      printf("%s is a symbolic link (%s)\n", dirent->d_name, file_name);  
    }
    else if(dirent->d_type != DT_DIR){
      for(int i = 0; i < level; i++){
        printf("    ");
      }
      printf("%s (%lld)\n", dirent->d_name, (long long) statbuf.st_size);   
    }
    else{
      for(int i = 0; i < level; i++){
        printf("    ");
      }
      level++;
      printf ("%s (%lld)\n", dirent->d_name, (long long) statbuf.st_size);
      char dir_path[PATH_MAX] = {0};
      strcat(dir_path, arg); strcat(dir_path, "/"); strcat(dir_path, dirent->d_name);
      traverse(dir_path, stat_arr);
    }
  }
  level--;
  closedir (parentDir);
  return arr_count;
}

#endif