#include <gsl/gsl_linalg.h>

#include <stdio.h>             // standard input/output
#include <stdlib.h>            // malloc
#include <math.h>              // fabs, sqrt, etc.
#include <time.h>              // time
#include <unistd.h>            // getpid
#include <gsl/gsl_rng.h>       // GNU Scientific Library
#include <gsl/gsl_cdf.h>       // GNU Scientific Library
#include <gsl/gsl_randist.h>   // GNU Scientific Library

#define pi 3.14159265358979323846

// Returns a random number b/w 0 & 1
double runif() {
  return (double) rand() / (double) RAND_MAX;
}



int main(int argc, char* argv[]) {
  int n = 1000; //Need to find an easy way to change this dynamically
  double mat[1000][11]; //need a dynamic way to change this also
  int i=0;
  int j=0;


}


