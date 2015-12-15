//https://www.gnu.org/software/gsl/manual/html_node/Matrices.html
#include <stdio.h>             // standard input/output
#include <stdlib.h>            // malloc
#include <math.h>              // fabs, sqrt, etc.
#include <time.h>              // time / set seed
#include <gsl/gsl_rng.h>       // GNU Scientific Library
#include <gsl/gsl_cdf.h>       // GNU Scientific Library
#include <gsl/gsl_randist.h>   // GNU Scientific Library
#include <gsl/gsl_linalg.h>    // GNU Scientific Library
#include <gsl/gsl_matrix.h>    // GNU Scientific Library
#include <gsl/gsl_statistics.h>// GNU Scientific Library
#include <gsl/gsl_blas.h>      // GSL Basic Linear Algebra
#define pi 3.14159265358979323846

// Reading Matrices ////////////////////////////////////////////////
int countFileRows(char* filename) {
  FILE *fp;
  int count = 0;  // Line counter (result)
  char c;  // To store a character read from file

  fp = fopen(filename, "r");
  // Extract characters from file and store in character c
  if (fp) { // check file existence
  for (c = getc(fp); c != EOF; c = getc(fp))
      if (c == '\n') // Increment count if this character is newline
          count = count + 1;
  }
  fclose(fp);

  return count;
}

int countFileCols(char* filename, char delim) {
  FILE *fp = fopen(filename, "r");
  char c;
  int count = 0;

  while( c=fgetc(fp) ) {
    if(c == EOF) {
      break; /* break if end of file */
    } else if (c == delim) {
      count += 1; /* otherwise add one to the count */
    } else if (c == '\n') {
      count += 1;
      break;
    }
  }
  fclose(fp);

  return count;
}

void readmatrix(gsl_matrix* m, char* filename) {
  FILE* f = fopen(filename, "r");
  gsl_matrix_fscanf(f, m);
  fclose(f);
}

gsl_matrix read_csv(char* filename, char dlm) {
  int n = countFileRows(filename);
  int k = countFileCols(filename,dlm);
  // Warning: In this way, memory is NOT freed by program, but by OS.
  //          USE CAUTION WITH BIG DATA!!!
  gsl_matrix* m = gsl_matrix_alloc(n,k);
  readmatrix(m,filename);
  return *m;
}

// Printing Matrix Info ////////////////////////////
int nrow(gsl_matrix* m) {return m -> size1;}
int ncol(gsl_matrix* m) {return m -> size2;}

void printmatrix(gsl_matrix m, char* filename) {
  FILE* f = fopen(filename, "w");
  int n = nrow(&m);
  int k = ncol(&m);
  
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < k; j++) {
      fprintf (f, "%f\t", gsl_matrix_get (&m, i, j));
    }
    fprintf (f, "\n");
  }
  fclose(f);
}
// Other Functions: /////////////////////////////////

// Returns a random number b/w 0 & 1
double runif() {
  return (double) rand() / (double) RAND_MAX;
}

// https://www.gnu.org/software/gsl/manual/html_node/BLAS-Support.html#BLAS-Support
// product of matrices
gsl_matrix prod (gsl_matrix a, gsl_matrix b) {
   // gsl_blas_dgemm: d=double, ge=general matrix, mm=matrix-matrix
   int n = nrow(&a);
   int k = ncol(&b);
   gsl_matrix* c = gsl_matrix_alloc(n,k);
   gsl_blas_dgemm(CblasNoTrans, CblasNoTrans,
                  1.0, &a, &b, 0.0, &c);
   return *c;
}
