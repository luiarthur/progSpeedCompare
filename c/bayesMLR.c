//https://www.gnu.org/software/gsl/manual/html_node/Matrices.html
#include <stdio.h>             // standard input/output
#include <stdlib.h>            // malloc
#include <math.h>              // fabs, sqrt, etc.
#include <time.h>              // time
#include "my_gsl.h"            // printing / reading matrices

// Returns a random number b/w 0 & 1
double runif() {
  return (double) rand() / (double) RAND_MAX;
}

double gibbs(int* n, int* k, gsl_matrix* mle) {
}


double ll(gsl_matrix* b, double s2) {
  gsl_matrix* c = gsl_matrix_alloc(1,1);
  gsl_matrix* out;
}

int main(int argc, char* argv[]) {
  //gsl_matrix* z, X, y, XXi, Xt;
  //gsl_matrix* mle, bb, ss, csb;
  //double a = 1;
  //double b = 1;
  //double s2 = 10;
  //double css = 1;
  //int B = 100000;

  char* filename = "../data/dat.txt";
  gsl_matrix m = read_csv(filename,' '); // my_gsl
  printf("%d%s%d\n",nrow(&m),"x",ncol(&m)); // my_gsl
  printmatrix(m,"fout.txt"); // my_gsl

  return 0;
}
