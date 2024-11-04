#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int total_points = 0;
int points_inside = 0;

void* function(void* arg) {
    int n = *(int*)arg;
    
    for (long i = 0; i < n; i++) {
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX; 

        // point is in circle if the hypotenuse (x^2 + y^2 ) is less than 1 (our circle is radius 1)
        if ((x * x + y * y) <= 1) { 
            points_inside++;
        }
        total_points++;
        //printf("%d and %d\n", points_inside, total_points);
    }
}

int main() {

    int n = 10000000; // number of random values we want

    pthread_t t;
    pthread_create(&t, NULL, function, &n);
    pthread_join(t, NULL);

    double result = 4.0 * ((double)points_inside / (double)total_points);
    printf("The approximated value of pi is: %f\n", result);

}