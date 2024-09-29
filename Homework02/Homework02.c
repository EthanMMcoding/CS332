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

void insertion_sort_str(char **arr, int size){
  for(int i = 0; i < size; i++){
    char *key = arr[i];
    int j = i - 1;
    while(j >= 0 && strcmp(arr[j], key) > 0){
      arr[j + 1] = arr[j];
      j -= 1;
    }
    arr[j + 1] = key;
  }
}

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

void print_stat(struct stat statbuf){
  printf("file type:                ");

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
  printf("I-Node number:            %ld\n", (long)statbuf.st_ino);

  printf("Mode:                     %lo (octal)\n", (unsigned long) statbuf.st_mode );

  printf("Link count:               %ld\n", (long) statbuf.st_nlink);

  printf("Ownership:                UID=%ld   GID=%ld\n", (long) statbuf.st_uid, (long) statbuf.st_gid);

  printf("Preferred I/O block size: %ld bytes\n", (long) statbuf.st_blksize);

  printf("Blocks allocated:         %lld\n", (long long) statbuf.st_blocks);

  printf("File size:                %lld\n", (long long) statbuf.st_size);

  printf("Last status change:       %s\n", ctime(&statbuf.st_ctim));
  printf("Last file access:         %s\n", ctime(&statbuf.st_atim));
  printf("Last modification:        %s\n", ctime(&statbuf.st_mtim));
}

void list_all_files(const char *arg){
  DIR *parentDir = opendir(arg);
  if (parentDir == NULL) { 
    printf ("Error opening directory '%s'\n", arg); 
    exit (-1);
  }
  struct dirent *dirent;
  static int level = 0;
  struct stat statbuf;
  int fd;
  if ((fd = open(arg, O_RDONLY)) == -1) {
		printf("Error opening file %s\n", arg);
		perror("open");
		exit(-1);
	}
	read(fd, &statbuf, sizeof(struct stat));
	close(fd);
  while((dirent = readdir(parentDir)) != NULL){ 
    if(strcmp(dirent->d_name, ".") == 0 || strcmp(dirent->d_name, "..") == 0){
      continue;
    }
    else if(strcmp(filetype(dirent->d_type), "directory") != 0){
      for(int i = 0; i < level; i++){
        printf("    ");
      }
      printf ("%s (%lld)\n", dirent->d_name, (long long) statbuf.st_size); 
    }
    else{
      for(int i = 0; i < level; i++){
        printf("    ");
      }
      level++;
      printf ("%s (%lld)\n", dirent->d_name, (long long) statbuf.st_size);
      char path[PATH_MAX] = {0};
      strcat(path, arg); strcat(path, "/"); strcat(path, dirent->d_name);
      list_all_files(path);
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
  int fd;
  if ((fd = open(arg, O_RDONLY)) == -1) {
		printf("Error opening file %s\n", arg);
		perror("open");
		exit(-1);
	}
	read(fd, &statbuf, sizeof(struct stat));
	close(fd);
  while((dirent = readdir(parentDir)) != NULL){ 
    if(strcmp(dirent->d_name, ".") == 0 || strcmp(dirent->d_name, "..") == 0){
      continue;
    }
    else if((long long) statbuf.st_size < size){
      continue;
    }
    else if(strcmp(filetype(dirent->d_type), "directory") != 0){
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
      list_all_files(path);
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
  int fd;
  if ((fd = open(arg, O_RDONLY)) == -1) {
		printf("Error opening file %s\n", arg);
		perror("open");
		exit(-1);
	}
	read(fd, &statbuf, sizeof(struct stat));
	close(fd);
  while((dirent = readdir(parentDir)) != NULL){ 
    if(strcmp(dirent->d_name, ".") == 0 || strcmp(dirent->d_name, "..") == 0){
      continue;
    }
    else if(strstr(dirent->d_name, pattern) == NULL){
      continue;
    }
    if(strcmp(filetype(dirent->d_type), "directory") != 0){
      for(int i = 0; i < level; i++){
        printf("    ");
      }
      printf ("%s (%lld)\n", dirent->d_name, (long long) statbuf.st_size); 
    }
    else{
      for(int i = 0; i < level; i++){
        printf("    ");
      }
      level++;
      printf ("%s (%lld)\n", dirent->d_name, (long long) statbuf.st_size);
      char path[PATH_MAX] = {0};
      strcat(path, arg); strcat(path, "/"); strcat(path, dirent->d_name);
      list_all_files(path);
    }
  }
  level--;
  closedir (parentDir);
}

void r(const char *arg){
  
}

int main(int argc, char **argv){

  list_all_files(argv[1]);

  // int opt;

  // while((opt = getopt(argc, argv, "Ss:f:r")) != -1)  
  //   {  
  //       switch(opt)  
  //       {  
  //           case 'S':  
  //           case 's':
  //             if(optarg != NULL){

  //             }  
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

  // int i;
  // struct stat buf;
  // char *ptr;

  // for(int i = 1; i < argc; i++){
  //   printf("%s: ", argv[i]);
  //   if(lstat(argv[i], &buf) < 0){
  //     printf("lstat error\n");
  //     continue;
  //   }
  //   if(S_ISREG(buf.st_mode)){
  //     ptr = "regular\n";
  //   }
  //   else if(S_ISDIR(buf.st_mode)){
  //     ptr = "directory\n";
  //   }
  //   else if(S_ISCHR(buf.st_mode)){
  //     ptr = "character special\n";
  //   }
  //   else if(S_ISBLK(buf.st_mode)){
  //     ptr = "block\n";
  //   }
  //   else if(S_ISFIFO(buf.st_mode)){
  //     ptr = "fifo\n";
  //   }
  //   else if(S_ISLNK(buf.st_mode)){
  //     ptr = "link\n";
  //   }
  //   else if(S_ISSOCK(buf.st_mode)){
  //     ptr = "socket\n";
  //   }
  //   else{
  //     ptr = "unknown mode\n";
  //   }
  //   printf("%s\n", ptr);
  // print_stat(buf);
  // }
  // exit(0);
}