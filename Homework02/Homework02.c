#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

typedef int TESTFUNC(char a, char b, char c);

typedef int MYFUNC(int a, int b);

char s(char a, char b, char c){
  if(a == 's'){
    return a;
  }
  else if(b == 's'){
    return b;
  }
  else{
    return c;
  }
}

void opfunc2(char a, char b, char c, TESTFUNC *f){
  return f(a, b, c);
}

int add(int a, int b) {
	printf("This is the add function\n");
	return a + b;
}

int sub(int a, int b) {
	printf("This is the subtraction function\n");
	return a - b;
}

int opfunc(int a, int b, MYFUNC *f) {
	return f(a, b);
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

/* will be the -S functionality required in homework */
void list_files(struct stat sb, char **path){
  DIR *dp;
  struct dirent *dp_buf;
  dp = opendir(path);
  if(!dp){
    printf("opendir error\n");
  }
  while(dp_buf = readdir(dp)){
    if(!dp_buf){
      printf("End of file reached or error reading\n");
    }
  }
  // printf("%s                        (%lld)\n", argv, (long long) sb.st_size); // should print out file name and its size
}

void traverse(){

}

int main(int argc, char *argv[]){

  int opt;

  while((opt = getopt(argc, argv, "Ss:f:r")) != -1)  
    {  
        switch(opt)  
        {  
            case 'S':  
            case 's':  
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

  int i;
  struct stat buf;
  char *ptr;

  for(int i = 1; i < argc; i++){
    printf("%s: ", argv[i]);
    if(lstat(argv[i], &buf) < 0){
      printf("lstat error\n");
      continue;
    }
    if(S_ISREG(buf.st_mode)){
      ptr = "regular\n";
    }
    else if(S_ISDIR(buf.st_mode)){
      ptr = "directory\n";
    }
    else if(S_ISCHR(buf.st_mode)){
      ptr = "character special\n";
    }
    else if(S_ISBLK(buf.st_mode)){
      ptr = "block\n";
    }
    else if(S_ISFIFO(buf.st_mode)){
      ptr = "fifo\n";
    }
    else if(S_ISLNK(buf.st_mode)){
      ptr = "link\n";
    }
    else if(S_ISSOCK(buf.st_mode)){
      ptr = "socket\n";
    }
    else{
      ptr = "unknown mode\n";
    }
    printf("%s\n", ptr);
  print_stat(buf);
  }
  exit(0);
}