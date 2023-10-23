#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_BYTES 100

int main(void) {
    char *arg[100];
    char temp[MAX_BYTES];
    char buf[MAX_BYTES];
    int len;
    int argc;
    pid_t pid;

    while (1) {
        printf("osh> ");
		// cout will only come out at the end if fflush isn't used
        fflush(stdout); //flushes the output buffer and moves the buffered data to console/disk 
		// reads MAX_BYTES bytes from file descriptor STDIN_FILENO into the buffer
        len = read(STDIN_FILENO, buf, MAX_BYTES);

        buf[len] = '\0';
        argc = 0; // argument count

        // parse input into arguments
        char *token = strtok(buf, " \n");
        while (token != NULL) {
            arg[argc] = strdup(token);
            argc++;
            token = strtok(NULL, " \n");
        }
        arg[argc] = NULL;

        // check if the command is "exit"
        if ((strcmp(arg[0], "exit") == 0) && argc == 1) {
            printf("Process end\n");
            break;
        }
        // else execute the command after the fork
        pid = fork();
        if (pid == 0) { // child process
            if (execvp(arg[0], arg) == -1) {
                perror("execvp");
                exit(1);
            }
        } else { // parent process
            wait(NULL);
            for (int i = 0; i < argc; i++) {
                free(arg[i]);
            }
        }
    }
    return 0;
}