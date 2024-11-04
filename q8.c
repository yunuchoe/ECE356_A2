#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int avg = 0;
int min = 0;
int max = 0;

int count = 0;


void* average(void* arg) {
    int* nums = (int*)arg;
    int sum = 0;
    for(int i = 0; i < count; i++){
        sum += nums[i];
    }
    avg = sum/count;
}

void* minimum(void* arg) {
    int* nums = (int*)arg;
    min = nums[0];
    for(int i = 0; i < count; i++){
        if (nums[i] < min){
            min = nums[i];
        }
    }
}

void* maximum(void* arg) {
    int* nums = (int*)arg;
    max = nums[0];
    for(int i = 0; i < count; i++){
        if (nums[i] > max){
            max = nums[i];
        }
    }
}


int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("ERROR: not enough arguments\n");
        return 0;
    }

    count = argc-1;
    int nums[count];

    for(int i = 0; i < count; i++){
        nums[i] = atoi(argv[i + 1]);
    }

    pthread_t t[3];
    pthread_create(&t[0], NULL, average, (void*)nums);
    pthread_create(&t[1], NULL, minimum, (void*)nums);
    pthread_create(&t[2], NULL, maximum, (void*)nums);

    for (int i = 0; i < 3; i++) {
        pthread_join(t[i], NULL);
    }

    printf("The program will report\n");
    printf("The average value is %d\n", avg);
    printf("The minimum value is %d\n", min);
    printf("The maximum value is %d\n", max);

}