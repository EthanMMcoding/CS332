#ifndef TRAVERSE

#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "file_struct.h"

/* returns number of files */

size_t traverse(const char *arg, file **file_arr){
  static size_t arr_count = 0;
  DIR *parentDir = opendir(arg);
  if (parentDir == NULL) { 
    printf("Error opening directory '%s'\n", arg); 
    exit (-1);
  }
  struct dirent *dirent;
  static int level = 0;
  struct stat statbuf;
  file curr_file;
  curr_file.level = level;
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
      *file_arr = (file*)malloc(arr_count * sizeof(file));
      if(*file_arr == NULL){
        printf("Error calling initial malloc");
        exit(-1);
      }
    }
    else{
      arr_count++;
      *file_arr = (file*)realloc(*file_arr, arr_count * sizeof(file));
      if(*file_arr == NULL){
        printf("Error reallocating\n");
        exit(-1);
      }
    }
    int len = strlen(dirent->d_name) + 1;
    curr_file.file_name = (char*)malloc(len);
    memccpy(curr_file.file_name, dirent->d_name, 0, len);
    curr_file.file_stat = statbuf;
    *(*file_arr + arr_count - 1) = curr_file;
    if(dirent->d_type == DT_LNK){
      char file_name[FILENAME_MAX];
      readlink(file_path, file_name, FILENAME_MAX);
      printf("sym linked file (%s)\n", file_name);
      curr_file.sym_linked_file = (char*)malloc(FILENAME_MAX+1);
      memcpy(curr_file.sym_linked_file, file_name, FILENAME_MAX);
      *(*file_arr + arr_count - 1) = curr_file;
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
      traverse(dir_path, file_arr);
    }
  }
  level--;
  closedir (parentDir);
  return arr_count;
}

#endif