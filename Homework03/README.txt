Homework03 README.txt

Name: Ethan Martignoni
BlazerID: Ethanmm
Project #: Homework #3

To compile:
  Using Makefile: make
  Without Makefile:
    gcc -Wall -g -c hw3.c -o hw3.o
    gcc -Wall -g -c traverse.c -o traverse.o
    gcc -Wall -g -o hw3 hw3.o word_counter.o traverse.o

To run:
  Using Makefile: make run ARGS="..."
  Without Makefile: ./hw3 ...

Clean up:
  Using Makefile: make clean
  Without Makefile: rm -f hw3