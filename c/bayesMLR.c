#include <stdio.h>             // standard input/output
#include <stdlib.h>            // malloc
#include <math.h>              // fabs, sqrt, etc.
#include <time.h>              // time
#include <unistd.h>            // getpid
#include <gsl/gsl_rng.h>       // GNU Scientific Library
#include <gsl/gsl_cdf.h>       // GNU Scientific Library
#include <gsl/gsl_randist.h>   // GNU Scientific Library
#include <gsl/gsl_linalg.h>    // GNU Scientific Library
#include <gsl/gsl_matrix.h>    // GNU Scientific Library

//#include "/data/arthurll/arthurPackages/c/vector/vector.h"


#define pi 3.14159265358979323846

// Returns a random number b/w 0 & 1
double runif() {
  return (double) rand() / (double) RAND_MAX;
}

double gibbs(int* n, int* k, gsl_matrix* mle) {
}

//void readmatrix(int n, int k, gsl_matrix* m, char* filename) {
//  FILE* file=fopen(filename, "r");
//  for (int i = 0; i < n; i++)
//    for (int j = 0; j < k; j++)
//      gsl_matrix_set (m, i, j, 0.23 + 100*i + j);
//  
//  //for (int i = 0; i < n; i++)  /* OUT OF RANGE ERROR */
//  //  for (int j = 0; j < k; j++)
//  //    printf ("m(%d,%d) = %g\n", i, j, 
//  //            gsl_matrix_get (m, i, j));
//}

int main(int argc, char* argv[]) {
  int n = 4;
  int k = 2;

  // initialize m
  gsl_matrix* m = gsl_matrix_alloc(n,k);

  // read data
  FILE* f = fopen("test/dat.txt", "r");
  gsl_matrix_fscanf(f, m);
  fclose(f);

  // write data
  FILE* o = fopen("fout.txt", "w");
  gsl_matrix_fprintf(o, m,"%f\t");
  fclose(o);


  // free memory
  gsl_matrix_free(m);
}
