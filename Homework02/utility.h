#ifndef PRINT_STAT

#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

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

#endif