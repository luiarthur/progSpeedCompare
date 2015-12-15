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

//https://www.gnu.org/software/gsl/manual/html_node/Matrices.html


#define pi 3.14159265358979323846

//////////////////////////////////////////////////////////////////
void printmatrix(gsl_matrix* m, int n, int k, char* filename) {
  FILE* f = fopen(filename, "w");
  
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < k; j++) {
      fprintf (f, "%f\t", gsl_matrix_get (m, i, j));
    }
    fprintf (f, "\n");
  }
  fclose(f);
}

void readmatrix(gsl_matrix* m, char* filename) {
  FILE* f = fopen(filename, "r");
  gsl_matrix_fscanf(f, m);
  fclose(f);
}

int nrow(gsl_matrix* m) {return m -> size1;}
int ncol(gsl_matrix* m) {return m -> size2;}
//////////////////////////////////////////////////

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
  gsl_matrix* z, X, y, XXi, Xt;
  gsl_matrix* mle, bb, ss, csb;
  double a = 1;
  double b = 1;
  double s2 = 10;
  double css = 1;
  int B = 100000;

  //int n = 1000;
  //int k = 11;
  //gsl_matrix* m = gsl_matrix_alloc(n,k);
  //readmatrix(m,"../data/dat.txt");
  //printf("%d",nrow(m));
  //printmatrix(m,n,k,"fout.txt");
  //gsl_matrix_free(m);

  return 0;
}
