#ifndef FILE_STRUCT
#define FILE_STRUCT
#include <sys/stat.h>

struct file{
  struct stat file_stat;
  int level;
  char *file_name;
  char *sym_linked_file;
  int filtered;
};

typedef struct file file;

#endif