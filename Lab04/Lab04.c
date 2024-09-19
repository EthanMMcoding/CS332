#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUFF_SIZE 4096

int main(int argc, char *argv[]){
  int read_file_descriptor, write_file_descriptor;
  char buf[BUFF_SIZE];
  long int n;
  long int x;

  if (argc != 3){
		printf("Usage: %s <source_filename> <destination_filename>\n", argv[0]);
		exit (-1);
	}

  if (!strcmp(argv[1], argv[2])){
    printf("Error file names are the same\n");
    exit(-1);
  }

  write_file_descriptor = open(argv[1], O_WRONLY|O_APPEND);
  read_file_descriptor = open(argv[2], O_RDONLY);

  if (read_file_descriptor == -1 || write_file_descriptor == -1){
		printf("Error with file open\n");
		exit (-1);
	}

  while((n = read(read_file_descriptor, buf, BUFF_SIZE)) > 0){
    if((x = write(write_file_descriptor, buf, n)) != n){
      printf("n is %lu, write is %lu\n", n, x);
      printf("Error writing to output file\n");
			exit (-1);
    }
  }
  if (n < 0){
		printf("Error reading input file\n");
		exit (-1);
	}

  close(read_file_descriptor);
	close(write_file_descriptor);

  return 0;
}