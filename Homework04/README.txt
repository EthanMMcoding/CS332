Homework04 README.txt

Name: Ethan Martignoni
BlazerID: Ethanmm
Project #: Homework #4

To compile:
  Using Makefile: make
  Without Makefile:
    gcc -Wall -pthread -o hw4 hw4.c

To run:
  Using Makefile: make run
  Without Makefile: ./hw4

Clean up:
  make clean

Linking error with -lpthread:
  When attempting to compile with -lpthread on code spaces this error occurs:
    /usr/bin/ld: /tmp/ccJ14cOY.o: in function `main':
    hw4.c:(.text+0x12e): undefined reference to `pthread_create'
    /usr/bin/ld: hw4.c:(.text+0x185): undefined reference to `pthread_join'
    /usr/bin/ld: hw4.c:(.text+0x2e8): undefined reference to `pthread_create'
    /usr/bin/ld: hw4.c:(.text+0x345): undefined reference to `pthread_join'
    collect2: error: ld returned 1 exit status
  compiling with -pthread works fine on codespaces