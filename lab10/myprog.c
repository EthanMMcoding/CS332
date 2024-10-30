/* 
 * Sample program to illustrate I/O streams and I/O redirection 
 * To Compile: gcc -Wall -o myprog myprog.c 
 */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv) {
	char name[BUFSIZ];

	pid_t pid = getpid();
	printf("[%d]Please enter your name: ", pid);
	scanf("%s", name);
	printf("%s\n", name);
	printf("[%d][stdout]: Hello %s!\n", pid, name);
	fprintf(stderr, "[%d][stderr]: Hello %s!\n", pid, name);

	return 0;
}
