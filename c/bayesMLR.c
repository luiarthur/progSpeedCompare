#include <stdio.h>             // standard input/output
#include <stdlib.h>            // malloc
#include <math.h>              // fabs, sqrt, etc.
#include <time.h>              // time
#include <unistd.h>            // getpid
#include <gsl/gsl_rng.h>       // GNU Scientific Library
#include <gsl/gsl_cdf.h>       // GNU Scientific Library
#include <gsl/gsl_randist.h>   // GNU Scientific Library
#include <gsl/gsl_linalg.h>    // GNU Scientific Library

//#include "/data/arthurll/arthurPackages/c/vector/vector.h"


#define pi 3.14159265358979323846

// Returns a random number b/w 0 & 1
double runif() {
  return (double) rand() / (double) RAND_MAX;
}



int main(int argc, char* argv[]) {


}


