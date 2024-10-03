#define _XOPEN_SOURCE 700
#define _DEFAULT_SOURCE

#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include "traverse.h"
#include "file_utility.h"

void S(const char *arg){
  DIR *parentDir = opendir(arg);  // open the directory
  if (parentDir == NULL) { 
    printf ("Error opening directory '%s'\n", arg); 
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
    strcat(file_path, arg); strcat(file_path, "/"); strcat(file_path, dirent->d_name);
    if(lstat(file_path, &statbuf) < 0){
        printf("lstat error\n");
      }
    else if(dirent->d_type == DT_LNK){
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
      S(dir_path);
    }
  }
  level--;
  closedir (parentDir);
}

void s(const char *arg, long long size){
  DIR *parentDir = opendir(arg);
  if (parentDir == NULL) { 
    printf ("Error opening directory '%s'\n", arg); 
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
    strcat(file_path, arg); strcat(file_path, "/"); strcat(file_path, dirent->d_name);
    if(lstat(file_path, &statbuf) < 0){
        printf("lstat error\n");
      }
    if((long long) statbuf.st_size < size){
      continue;
    }
    if(S_ISLNK(statbuf.st_mode)){
      char file_name[FILENAME_MAX];
      readlink(file_path, file_name, FILENAME_MAX);
      stat(file_path, &statbuf);
      printf("%s is a symbolic link (%s)\n", dirent->d_name, file_name);  
    }
    else if(strcmp(filetype(dirent->d_type), "directory") != 0){
      char file_path[PATH_MAX] = {0};
      strcat(file_path, arg); strcat(file_path, "/"); strcat(file_path, dirent->d_name);
      for(int i = 0; i < level; i++){
        printf("    ");
      }
      printf("%s\n", dirent->d_name); 
    }
    else{
      for(int i = 0; i < level; i++){
        printf("    ");
      }
      level++;
      printf("%s\n", dirent->d_name);
      char path[PATH_MAX] = {0};
      strcat(path, arg); strcat(path, "/"); strcat(path, dirent->d_name);
      s(path, size);
    }
  }
  level--;
  closedir (parentDir);
}

void f(const char *arg, char *pattern){
  DIR *parentDir = opendir(arg);
  if (parentDir == NULL) { 
    printf ("Error opening directory '%s'\n", arg); 
    exit (-1);
  }
  struct dirent *dirent;
  static int level = 0;
  struct stat statbuf;
  while((dirent = readdir(parentDir)) != NULL){ 
    if(strcmp(dirent->d_name, ".") == 0 || strcmp(dirent->d_name, "..") == 0){
      continue;
    }
    else if(strstr(dirent->d_name, pattern) == NULL){
      continue;
    }
    if(strcmp(filetype(dirent->d_type), "directory") != 0){
      char file_path[PATH_MAX] = {0};
      strcat(file_path, arg); strcat(file_path, "/"); strcat(file_path, dirent->d_name);
      if(lstat(file_path, &statbuf) < 0){
        printf("lstat error\n");
      }
      for(int i = 0; i < level; i++){
        printf("    ");
      }
      printf ("%s\n", dirent->d_name); 
    }
    else{
      for(int i = 0; i < level; i++){
        printf("    ");
      }
      level++;
      printf ("%s\n", dirent->d_name);
      char path[PATH_MAX] = {0};
      strcat(path, arg); strcat(path, "/"); strcat(path, dirent->d_name);
      f(path, pattern);
    }
  }
  level--;
  closedir (parentDir);
}

void r(const char *arg){
  
}

int main(int argc, char **argv){

  if(argc < 2){
    printf("Usage: %s <dirname>, -s<file size in bytes>, -S, -f<string pattern>, -r\n", argv[0]);
    exit(-1);
  }

  file **file_arr = malloc(sizeof(struct stat*));
  if (file_arr == NULL) {
    printf("Error allocating memory for stat_arr\n");
    exit(-1);
}

  *file_arr = malloc(sizeof(struct stat));
  if(*file_arr == NULL){
      printf("Error allocating memory for stat_arr1\n");
      free(file_arr);
      exit(-1);
  }

  size_t arr_count = traverse(argv[1], file_arr);
  printf("\n");
  
  for(int i = 0; i < arr_count; i++){
    printf("file type:                ");
    switch ((*(*file_arr + i)).file_stat.st_mode & S_IFMT){
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

  // size_t size = sizeof(stat_arr)/sizeof(struct stat);

  // for(int i = 0; i < size; i++){
  //   printf("file type:                ");
  //   switch ((stat_arr + i)->st_mode & S_IFMT){
  //   case S_IFREG: printf("regular\n");   break;
  //   case S_IFDIR: printf("directory\n"); break;
  //   case S_IFCHR: printf("character\n"); break;
  //   case S_IFBLK: printf("block\n");     break;
  //   case S_IFIFO: printf("FIFO/pipe\n"); break;
  //   case S_IFLNK: printf("symlink\n");   break;
  //   case S_IFSOCK: printf("socket\n");   break;
  //   default :
  //     printf("unkown?\n");
  //     break;
  //   }
  // }


  // S(argv[1]);
  // printf("\n");
  // printf("\n");
  // printf("\n");
  // s(argv[1], 100);
  // printf("\n");
  // printf("\n");
  // printf("\n");
  // f(argv[1], "p");

  // int opt;

  // while((opt = getopt(argc, argv, "Ss:f:r")) != -1)  
  //   {  
  //       switch(opt)  
  //       {  
  //           case 'S':
  //             S(argv[argc-1]);
  //             break;
  //           case 's':
  //             if(optarg != NULL){
  //                s(argv[argc-1], (long long)optarg);
  //             }
  //             break;
  //           case 'r':  
  //               printf("option: %c\n", opt);  
  //               break;  
  //           case 'f':  
  //               printf("filename: %s\n", optarg);  
  //               break;  
  //           case ':':  
  //               printf("option needs a value\n");  
  //               break;  
  //           case '?':  
  //               printf("unknown option: %c\n", optopt); 
  //               break;  
  //       }  
  //   } 
}