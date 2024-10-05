#ifndef FILE_STRUCT
#define FILE_STRUCT

#include <sys/stat.h>

struct file{
  struct stat file_stat;
  char *file_name;
  char *sym_linked_file;
  char *parent_dir_path;
  int level;
  int filtered;
};

typedef struct file file;

#endif