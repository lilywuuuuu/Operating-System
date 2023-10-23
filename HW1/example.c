#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void show(int fork_id) {
    printf("Fork %d. I'm the child %d, my parent is %d.\n", fork_id, getpid(), getppid());
}

int main() {
    printf("Main Process ID: %d\n\n", getpid());
    
    pid_t pid;
    pid = fork(); // Fork 1
    if (pid == 0) { // process
        show(1);
    } else if (pid > 0) { // main
        wait(NULL);
        pid = fork(); // Fork 2
        if (pid == 0) { // process
            show(2);
        } else { // main
            wait(NULL);
        }
    }
    
    pid = fork(); // Fork 3
    if (pid == 0) { // porcess
        show(3);
    } else { // main
        wait(NULL);
    }

    return 0;
}
