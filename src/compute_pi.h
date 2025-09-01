#ifndef COMPUTE_PI_H
#define COMPUTE_PI_H

// compute PI using the first n terms of the
// Bailey Borwein Plouffe expansion, serially
double compute_PI_serial(const int n);

// compute PI using the first n terms of the
// Bailey Borwein Plouffe expansion, concurrently
double compute_PI_concurrent(const int n, const short int nthreads);

#endif