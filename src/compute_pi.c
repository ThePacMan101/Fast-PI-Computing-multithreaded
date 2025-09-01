#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "compute_pi.h"

double compute_PI_serial(const int n){
    double PI_approximation = 0;
    for (int k = 0 ; k < n ; ++k){
        double k_th_term = ((double)4/(8*k+1) - (double)2/(8*k+4) - (double)1/(8*k+5) - (double)1/(8*k+6))*(double)1/pow(16,k);
        PI_approximation += k_th_term;
    }
    return PI_approximation;
}

typedef struct{
    short int id, nthreads;
    int n;
}__thread_args;
void* __thread_compute_PI_concurrent(void* void_args){
    // initialize funcition arguments
    __thread_args * args = (__thread_args*)void_args;
    int slice = args->n/args->nthreads;
    int start = args->id*slice;
    int end = start + slice;
    if(end > args->n) end = args->n;

    // allocate memory for return value
    double *some_of_PI = malloc(sizeof(double));
    
    // compute some of PI
    for (int k = start ; k < end ; ++k){
        double k_th_term = ((double)4/(8*k+1) - (double)2/(8*k+4) - (double)1/(8*k+5) - (double)1/(8*k+6))*(double)1/pow(16,k);
        *some_of_PI += k_th_term;
    }

    // free argument memmory
    free(void_args);
    
    // return some of PI
    pthread_exit(some_of_PI);
}

double compute_PI_concurrent(int n, short int nthreads){
    // create threads
    pthread_t *tid = (pthread_t*) calloc(sizeof(pthread_t),nthreads);
    if(!tid){
        fprintf(stderr,"[ERROR] Couldn't allocate space for threads\n");
        exit(2);
    } 
    for(int i = 0 ; i < nthreads ; ++i){
        __thread_args * args = (__thread_args*) malloc(sizeof(__thread_args));
        args->nthreads=nthreads;
        args->id=i;
        args->n=n;
        pthread_create(&tid[i],NULL,__thread_compute_PI_concurrent,(void*) args);
    }

    double PI_approximation = 0;
    double * some_of_PI;
    for(int i = 0 ; i < nthreads ; ++i){
        pthread_join(tid[i],(void**)&some_of_PI);
        PI_approximation += *some_of_PI;
        free(some_of_PI);
    }

    return PI_approximation;
}