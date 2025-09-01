#include <stdio.h>
#include "compute_pi.h"

int main(int argc, char ** argv){
    if(argc != 3){
        fprintf(stderr,"[ERROR] try: $ <PI-accuracy> <nthreads>\n");
        exit(1);
    }
}