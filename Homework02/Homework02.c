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

  r(*file_arr, arr_count);

  for(int i = 0; i < arr_count; i++){
    file file_i = *(*file_arr+i);
    printf("file name: %s filesize: %ld\n", file_i.file_name, file_i.file_stat.st_size);
  }

  // int opt;
  // char *opt_arr = (char*)malloc(sizeof(char));
  // int opt_counter = 0;
  // char *string_pattern = (char*)malloc(sizeof(char));
  // int file_size_in_bytes = 0;

  // while((opt = getopt(argc, argv, "Ss:f:r")) != -1) {
  //   switch(opt){  
  //     case 'S':
  //       opt_counter++;
  //       opt_arr = (char*)realloc(*opt_arr, opt_counter * sizeof(char));
  //       *(opt_arr + opt_counter - 1) = "S";
  //     break;
  //     case 's':
  //       opt_counter++;
  //       opt_arr = (char*)realloc(*opt_arr, opt_counter * sizeof(char));
  //       *(opt_arr + opt_counter - 1) = "s";
  //       if(optarg){
  //         file_size_in_bytes = optarg;
  //         s(argv[argc-1], arr_count, (long long)optarg);
  //       }
  //       else{
  //         printf("Usage: -s <file size in bytes>");
  //       }
  //     break;
  //     case 'r':  
  //       printf("option: %c\n", opt);  
  //     break;  
  //     case 'f':  
  //       opt_counter++;
  //       opt_arr = (char*)realloc(*opt_arr, opt_counter * sizeof(char));
  //       *(opt_arr + opt_counter) = "f";
  //       if(optarg){
  //         string_pattern = (char*)malloc(strlen(optarg) * sizeof(char));
  //       }
  //       else{
  //         printf("Usage: -f <string pattern>");
  //       }
  //     break;
  //     case ':':  
  //       printf("option needs a value\n");  
  //      break;  
  //     case '?':  
  //       printf("unknown option: %c\n", optopt); 
  //     break;  
  //   }
  // }
}