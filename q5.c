#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int n = 0;


    pid_t f = fork();

    if(f < 0){
        printf("Child creation failed\n");
        return 0;
    }else if(f == 0){ // child
        printf("CHILD: Taking off\n");
        printf("CHILD: Here's my PID: %d\n", getpid());
    }else if(f > 0){ // parent
        wait(NULL);

        printf("PARENT: Landing\n");
        printf("PARENT: Here's my PID: %d\n", getpid());
    } 
    return 0;
}