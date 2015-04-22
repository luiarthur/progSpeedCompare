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
//#include "/data/arthurll/arthurPackages/c/vector/vector.h"

#define pi 3.14159265358979323846

double runif(){
  return (double)rand()/(double)RAND_MAX;
}

// http://ftp.arl.mil/random/random.pdf
int rpois(double lam) {
  double b=1;
  int i;
  for (i=0; b>=exp(-lam); i++) b *= runif();
  return i-1;
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

void printm(vector M) {
  //Prints the matrix M
  for (int i=0; i<vector_count(&M); i++) {
    for (int j=0; j<vector_count(vector_get(&M,i));j++) {
      printf("%d",vector_get(vector_get(&M,i),j));
      printf("%s","  ");
    }
    printf("\n");
  }
}

int main(void) {
  vector r1;
  vector r2;
  vector M;

  vector_init(&r1);
  vector_init(&r2);
  vector_init(&M);

  vector_add(&r1,1);
  vector_add(&r1,2);
  vector_add(&r2,3);
  vector_add(&r2,4);
  vector_add(&r2,5);

  vector_add(&M,&r1);
  vector_add(&M,&r2);

  printm(M);

  return 0;
}
