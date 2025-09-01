#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "compute_pi.h"

int main(int argc, char ** argv){
    if(argc != 3){
        fprintf(stderr,"[ERROR] try: $ <PI-accuracy> <nthreads>\n");
        exit(1);
    }
    const int N = atoi(argv[1]);
    const short int nthreads = atoi(argv[2]);
    double PI_approximation;


    clock_t start = clock();
    if (nthreads == 1){
        PI_approximation = compute_PI_serial(N);
    }else{
        PI_approximation = compute_PI_concurrent(N,nthreads);
    }
    clock_t end = clock();

    float ms_spent = (end-start);

    printf("The approximation for PI is: %.20lf\n",PI_approximation);
    printf("proccess took %.2f ms\n",ms_spent);

}