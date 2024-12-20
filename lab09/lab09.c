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
  char *buf = "Waiting for ctrl+\\ to end the process\n";
  
  switch(signo){
    case SIGINT:
      printf("\nParent overriding SIGINT signal %d, waiting for ctrl+\\ \n", signo);
      for(;;)
          pause();
      break;
    case SIGTSTP:
      printf("\nParent overriding SIGTSTP signal %d, waiting for ctrl+\\ \n", signo);
      for(;;)
          pause();
      break;
    default:
      printf("\nRecieved signal %d\n", signo);
      break;
  }
  fflush(stdout);
  fwrite(buf, sizeof(char), 40, stdout);
  fflush(stdout);
}

int main(int argc, char **argv) {

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
        int status;
        wait(&status); /* get child process status */
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
