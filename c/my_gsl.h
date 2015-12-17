// https://www.gnu.org/software/gsl/manual/html_node/Matrices.html
// https://github.com/Blei-Lab/diln/blob/master/gsl_wrapper.c
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
  // Count number of rows in file "filename"
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
  // Count number of columns in file "filename" (with delimiter delim)
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

void read_csv(char* filename, gsl_matrix* m) {
  // Read a csv into matrix m
  FILE* f = fopen(filename, "r");
  gsl_matrix_fscanf(f, m);
  fclose(f);
}

// Printing Matrix Info ////////////////////////////

void print_matrix(gsl_matrix* m, char* filename) {
  // print matrix to filename or stdout if filename == ""
  FILE* f;
  if (filename == "") {
    f = stdout;
    printf("\n");
  } else {
    f = fopen(filename, "w");
  }
  int n = m->size1;
  int k = m->size2;
  
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < k; j++) {
      fprintf (f, "%g\t", gsl_matrix_get (m, i, j));
    }
    fprintf (f, "\n");
  }

  if (filename == "") {
    printf("\n");
  } else {
    fclose(f);
  }
}

void print_matrix_dims(gsl_matrix* m) {
  // print dimensions of matrix m
  printf("%d%s%d\n",m->size1,"x",m->size2);
}

// Other Functions: /////////////////////////////////
double runif() {
  // Returns a random number b/w 0 & 1
  return (double) rand() / (double) RAND_MAX;
}
