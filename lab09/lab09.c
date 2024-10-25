/* Simple program to illustrate the use of fork-exec-wait pattern. 
 * This version uses execvp and command-line arguments to create a new process.
 * To Compile: gcc -Wall forkexecvp.c
 * To Run: ./a.out <command> [args]
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

pid_t pid;

static void handle_parent_interupts(int signo){
  
  switch(signo){
    case SIGINT:
      printf("\nParent overriding SIGINT signal %d, waiting for ctrl+\\ \n", signo);
      break;
    case SIGTSTP:
      printf("\nParent overriding SIGTSTP signal %d, waiting for ctrl+\\ \n", signo);
      break;
    default:
      printf("Recieved signal %d\n", signo);
      break;
  }
  fflush(stdout);
  signal(signo, handle_parent_interupts);
}

int main(int argc, char **argv) {
    int status;

    if (argc < 2) {
        printf("Usage: %s <command> [args]\n", argv[0]);
        exit(-1);
    }

    pid = fork();
    if (pid == 0) { /* this is child process */
        execvp(argv[1], &argv[1]);
        printf("If you see this statement then execl failed ;-(\n");
	      perror("execvp");
	      exit(-1);
    } else if (pid > 0) { /* this is the parent process */
        if (signal(SIGINT, handle_parent_interupts) == SIG_ERR){
          printf("Unable to catch SIGINT\n");
        }
        if (signal(SIGTSTP, handle_parent_interupts) == SIG_ERR){
          printf("Unable to catch SIGTSTP\n");
        }
        printf("Wait for the child process to terminate\n");
        wait(&status); /* wait for the child process to terminate */
        if (WIFEXITED(status)) { /* child process terminated normally */
            printf("Child process exited with status = %d\n", WEXITSTATUS(status));
        } else { /* child process did not terminate normally */
            printf("Child process did not terminate normally!\n");
            /* look at the man page for wait (man 2 wait) to determine
               how the child process was terminated */
        }
    } else { /* we have an error */
        perror("fork"); /* use perror to print the system error message */
        exit(EXIT_FAILURE);
    }
    
    printf("[%ld]: Exiting program .....\n", (long)getpid());

    return 0;
}
