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
#include "options.h"
#include "file_struct.h"

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
  
  // for(int i = 0; i < arr_count; i++){
  //   printf("file type:                ");
  //   switch ((*(*file_arr + i)).file_stat.st_mode & S_IFMT){
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

  int opt;

  while((opt = getopt(argc, argv, "Ss:f:r")) != -1)  
    {
        switch(opt)  
        {  
            case 'S':
            printf("\n");
              S(*file_arr, arr_count);
              break;
            case 's':
              // if(optarg != NULL){
              //    s(argv[argc-1], (long long)optarg);
              // }
              break;
            case 'r':  
                printf("option: %c\n", opt);  
                break;  
            case 'f':  
                printf("filename: %s\n", optarg);  
                break;  
            case ':':  
                printf("option needs a value\n");  
                break;  
            case '?':  
                printf("unknown option: %c\n", optopt); 
                break;  
        }
    }
}