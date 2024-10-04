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
  static size_t file_count = 0;
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
    if(!file_count){
      file_count++;
      *file_arr = (file*)malloc(file_count * sizeof(file));
      if(*file_arr == NULL){
        printf("Error calling initial malloc");
        exit(-1);
      }
    }
    else{
      file_count++;
      *file_arr = (file*)realloc(*file_arr, file_count * sizeof(file));
      if(*file_arr == NULL){
        printf("Error reallocating\n");
        exit(-1);
      }
    }
    int len = strlen(dirent->d_name) + 1;
    curr_file.file_name = (char*)malloc(len);
    memcpy(curr_file.file_name, dirent->d_name, len);
    curr_file.file_stat = statbuf;
    curr_file.filtered = 0;
    *(*file_arr + file_count - 1) = curr_file;
    if(dirent->d_type == DT_LNK){
      char file_name[FILENAME_MAX];
      readlink(file_path, file_name, FILENAME_MAX);
      curr_file.sym_linked_file = (char*)malloc(FILENAME_MAX+1);
      memcpy(curr_file.sym_linked_file, file_name, FILENAME_MAX);
      *(*file_arr + file_count - 1) = curr_file;
    }
    else if(dirent->d_type == DT_DIR){
      level++;
      traverse(file_path, file_arr);
    }
  }
  level--;
  closedir(parentDir);
  return file_count;
}

#endif