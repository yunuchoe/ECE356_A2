#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

    int shareData = 10;
    int exit_status;

    pid_t f = fork();
    pid_t grandchild;

    if(f < 0){
        printf("Child creation failed\n");
        return 0;
    }else if(f == 0){ // child
        wait(&exit_status);

        printf("CHILD: I am the child process!\n");
        printf("CHILD: Here's my PID: %d\n", getpid());
        printf("CHILD: My parent's PID is: %d\n", getppid());
        printf("CHILD: SharedData = %d\n", shareData);
        shareData = 20;
        printf("CHILD: Changing SharedData to 20\n");

        printf("CHILD: Creating a grandchild process...\n\n"); 
        printf("CHILD FORK:\n");
        printf("CHILD: SharedData = %d\n", shareData);
        grandchild = fork();
            if(grandchild < 0){ // failed
                printf("Grandchild creation failed\n");
                return 0;
            }else if(grandchild == 0){ // child child = grand child
                    printf("GRANDCHILD: I am the grandchild rocess!\n");
                    printf("GRANDCHILD: Here's my PID: %d\n", getpid());
                    printf("GRANDCHILD: My parent's PID is: %d\n", getppid());
                    printf("GRANDCHILD: Sleeping for 1 second...\n");
                    sleep(1);
                    //exit(0);
            }else if(grandchild > 0){ // child parent = child
                wait(NULL);
            }
    }else if(f > 0){ // parent
        printf("PARENT: I am the parent Process\n");
        printf("PARENT: Here's my PID: %d\n", getpid());
        printf("PARENT: The value of my copy of childpid is: %d\n", f);
        printf("PARENT: I will now wait for my child to exit\n\n");

        waitpid(f, 0, 0);  // Parent waits for child to finish
        printf("PARENT: Child's exit code is: %d\n", exit_status);
        printf("PARENT: SharedData = %d (unchanged in parent)\n", shareData);
        printf("PARENT: Goodbye!\n");
    } 
    return 0;
}