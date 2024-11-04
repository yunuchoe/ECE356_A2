#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    
    int fd[2];
    int num;
    pipe(fd);
    
    pid_t f = fork();

    if(f < 0){
        printf("Child creation failed\n");
        return 0;
    }else if(f == 0){ // child
        sleep(1);
        read(fd[0], &num, sizeof(int));
        
        //print results
        printf("%d, ", num); // inital number wont be inside the loop but must still be printed
        while(num != 1){
            if(num%2 == 0){ // even
                num = num / 2;
            }else{ // odd
                num = (3*num) + 1;
            }
            if(num != 1){
                printf("%d, ", num);
            }
        }
        printf("%d", num); // print 1 without the ,
    }else if(f > 0){ // parent
        printf("Give a starting positive integer number num = ");
        scanf("%d", &num);
        if(num <= 0){
            printf("Error: a non positive integer was given\n");
            return 0;
        }
        write(fd[1], &num, sizeof(int));

        wait(NULL);
        printf("\nThe process is complete\n");
    } 
    return 0;
}