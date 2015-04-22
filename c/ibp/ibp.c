// ibp.c

#include <stdio.h>             // standard input/output
#include <stdlib.h>            // malloc
#include <math.h>              // fabs, sqrt, etc.
#include <time.h>              // time
#include <unistd.h>            // getpid
#include <gsl/gsl_rng.h>       // GNU Scientific Library
#include <gsl/gsl_cdf.h>       // GNU Scientific Library
#include <gsl/gsl_randist.h>   // GNU Scientific Library
#include "vector/vector.h"

#define pi 3.14159265358979323846

/*
double runif(){
  return (double)rand()/(double)RAND_MAX;
}

int sum(int* x) {
  double out = 0;
  for(int i=0; i<vector_count(x); i++) {
    out = out + x[i];
  }
  return out;
}

void ribp(int* n, int* x, double* a, int* z) {
  // a is alpha
  // n is the number of customers
  // x is an array (of length n) of the new dishes each customer takes

  int y = 0;
  for (int i=0; i<*n; i++) {
    for (int j=0; j<y; j++) {
      
    }
  }

}
*/

int main(void) {
  vector v;
  vector_init(&v);

  vector_add(&v,1);
  vector_add(&v,3);
  vector_add(&v,2);
  vector_add(&v,4);

  printf("First Round:\n");
  for (int i=0; i<vector_count(&v); i++){
    printf("%s\n", vector_get(&v,i));
  }  
  
  return 0;
}
