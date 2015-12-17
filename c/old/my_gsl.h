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

gsl_matrix* read_csv(char* filename, char dlm) {
  int n = countFileRows(filename);
  int k = countFileCols(filename,dlm);
  // Warning: In this way, memory is NOT freed by program, but by OS.
  //          USE CAUTION WITH BIG DATA!!!
  gsl_matrix* m = gsl_matrix_alloc(n,k);
  readmatrix(m,filename);
  return m;
}

// Printing Matrix Info ////////////////////////////
int nrow(gsl_matrix* m) {return m -> size1;}
int ncol(gsl_matrix* m) {return m -> size2;}


void print_matrix(gsl_matrix* m, char* filename) {
  FILE* f;
  if (filename == "") {
    f = stdout;
    printf("\n");
  } else {
    f = fopen(filename, "w");
  }
  int n = nrow(m);
  int k = ncol(m);
  
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

void print_mat(gsl_matrix*m) {
  print_matrix(m,"");
}

void print_matrix_dims(gsl_matrix* m) {
  printf("%d%s%d\n",nrow(m),"x",ncol(m)); // my_gsl
}
// Other Functions: /////////////////////////////////

// Returns a random number b/w 0 & 1
double runif() {
  return (double) rand() / (double) RAND_MAX;
}

// https://www.gnu.org/software/gsl/manual/html_node/BLAS-Support.html#BLAS-Support
gsl_matrix* mat_cp(gsl_matrix* X) {
  int n = nrow(X);
  int k = ncol(X);
  gsl_matrix* Y = gsl_matrix_alloc(n,k);
  gsl_matrix_memcpy(Y,X);
  return Y;
} //tested

gsl_matrix* mat_add (gsl_matrix* A, gsl_matrix* B) {
  gsl_matrix* C = mat_cp(A);
  gsl_matrix_add(C,B);
  return C;
}//tested

gsl_matrix* mat_add_c (gsl_matrix* A, double c) {
  gsl_matrix* X = mat_cp(A);
  gsl_matrix_add_constant(X,c);
  return X;
}//tested

gsl_matrix* mat_sub (gsl_matrix* A, gsl_matrix* B) {
  gsl_matrix* C = mat_cp(A);
  gsl_matrix_sub(C,B);
  return C;
}//tested

gsl_matrix* mat_had_prod (gsl_matrix* A, gsl_matrix* B) {
  gsl_matrix* C = mat_cp(A);
  gsl_matrix_mul_elements(C,B);
  return C;
}//tested
gsl_matrix* mat_had_div (gsl_matrix* A, gsl_matrix* B) {
  gsl_matrix* C = mat_cp(A);
  gsl_matrix_div_elements(C,B);
  return C;
}//tested

gsl_matrix* mat_I(int n) {
  gsl_matrix* I = gsl_matrix_alloc(n,n);
  gsl_matrix_set_identity(I);
  return I;
}//tested

gsl_matrix* mat_scale (gsl_matrix* A, double s) {
  gsl_matrix* X = mat_cp(A);
  gsl_matrix_scale(X,s);
  return X;
}//tested

// product of matrices
gsl_matrix* mat_prod (gsl_matrix* A, gsl_matrix* B) {
   // gsl_blas_dgemm: d=double, ge=general matrix, mm=matrix-matrix
   int n = nrow(A);
   int k = ncol(B);
   gsl_matrix* C = gsl_matrix_alloc(n,k);
   double a = 1;
   double b = 0;
   gsl_blas_dgemm(CblasNoTrans, CblasNoTrans,
                  a, A, B, b, C);

   return C; // a*AB+bC
}//tested

gsl_matrix* mat_t (gsl_matrix* X) {
  int n = nrow(X);
  int k = ncol(X);

  gsl_matrix* Xt = gsl_matrix_alloc(k,n);
  gsl_matrix_transpose_memcpy(Xt,X);

  return Xt;
}//tested


gsl_matrix* mat_get(gsl_matrix* X, size_t r1, size_t r2, size_t c1, size_t c2) {
  gsl_matrix_view y = gsl_matrix_submatrix(X,r1,c1,r2-r1+1,c2-c1+1);
  gsl_matrix* Y = gsl_matrix_alloc(r2-r1+1,c2-c1+1);
  gsl_matrix_memcpy(Y,&y.matrix);
  return Y;
} //tested

gsl_matrix* mat_row(gsl_matrix* X, size_t r) {
  int k = ncol(X);
  gsl_matrix_view y = gsl_matrix_submatrix(X,r,0,1,k);
  gsl_matrix* Y = gsl_matrix_alloc(1,k);
  gsl_matrix_memcpy(Y,&y.matrix);
  return Y;
} //CHECK. compare gsl_matrix_get_row

gsl_matrix* mat_col(gsl_matrix* X, size_t k) {
  int r = nrow(X);
  gsl_matrix_view y = gsl_matrix_submatrix(X,0,k,r,1);
  gsl_matrix* Y = gsl_matrix_alloc(r,1);
  gsl_matrix_memcpy(Y,&y.matrix);
  return Y;
} //CHECK. compare gsl_matrix_get_col


gsl_matrix* mat_inv(gsl_matrix* X) {
  int n = nrow(X); // must be square!

  gsl_matrix* LU = mat_cp(X);
  gsl_matrix* Xi = gsl_matrix_alloc(n,n);
  gsl_permutation *P = gsl_permutation_alloc(n);
  int s;

  gsl_linalg_LU_decomp(LU,P,&s);
  gsl_linalg_LU_invert(LU,P,Xi);
  gsl_permutation_free(P);
  
  return Xi;
}//tested


static inline 
double quiet_sqrt (double x)  
{
  return sqrt(x);
}

int
my_gsl_linalg_cholesky_decomp (gsl_matrix * A)
{
  const size_t M = A->size1;
  const size_t N = A->size2;

  if (M != N)
    {
      GSL_ERROR("cholesky decomposition requires square matrix", GSL_ENOTSQR);
    }
  else
    {
      size_t i,j,k;
      int status = 0;

      /* Do the first 2 rows explicitly.  It is simple, and faster.  And
       * one can return if the matrix has only 1 or 2 rows.  
       */

      double A_00 = gsl_matrix_get (A, 0, 0);
      
      double L_00 = quiet_sqrt(A_00);
      
      if (A_00 <= 0)
        {
          status = GSL_EDOM ;
        }

      gsl_matrix_set (A, 0, 0, L_00);
  
      if (M > 1)
        {
          double A_10 = gsl_matrix_get (A, 1, 0);
          double A_11 = gsl_matrix_get (A, 1, 1);
          
          double L_10 = A_10 / L_00;
          double diag = A_11 - L_10 * L_10;
          double L_11 = quiet_sqrt(diag);
          
          if (diag <= 0)
            {
              status = GSL_EDOM;
            }

          gsl_matrix_set (A, 1, 0, L_10);        
          gsl_matrix_set (A, 1, 1, L_11);
        }
      
      for (k = 2; k < M; k++)
        {
          double A_kk = gsl_matrix_get (A, k, k);
          
          for (i = 0; i < k; i++)
            {
              double sum = 0;

              double A_ki = gsl_matrix_get (A, k, i);
              double A_ii = gsl_matrix_get (A, i, i);

              gsl_vector_view ci = gsl_matrix_row (A, i);
              gsl_vector_view ck = gsl_matrix_row (A, k);

              if (i > 0) {
                gsl_vector_view di = gsl_vector_subvector(&ci.vector, 0, i);
                gsl_vector_view dk = gsl_vector_subvector(&ck.vector, 0, i);
                
                gsl_blas_ddot (&di.vector, &dk.vector, &sum);
              }

              A_ki = (A_ki - sum) / A_ii;
              gsl_matrix_set (A, k, i, A_ki);
            } 

          {
            gsl_vector_view ck = gsl_matrix_row (A, k);
            gsl_vector_view dk = gsl_vector_subvector (&ck.vector, 0, k);
            
            double sum = gsl_blas_dnrm2 (&dk.vector);
            double diag = A_kk - sum * sum;

            double L_kk = quiet_sqrt(diag);
            
            if (diag <= 0)
              {
                status = GSL_EDOM;
              }
            
            gsl_matrix_set (A, k, k, L_kk);
          }
        }

      /* Now copy the transposed lower triangle to the upper triangle,
       * the diagonal is common.  
       */
      
      for (i = 1; i < M; i++)
        {
          for (j = 0; j < i; j++)
            {
              double A_ij = 0;//gsl_matrix_get (A, i, j);
              gsl_matrix_set (A, j, i, A_ij);
            }
        } 
      
      if (status == GSL_EDOM)
        {
          GSL_ERROR ("matrix must be positive definite", GSL_EDOM);
        }
      
      return GSL_SUCCESS;
    }
}

gsl_matrix* mat_chol(gsl_matrix* X) {
  int n = nrow(X);
  gsl_matrix* A = mat_cp(X);
  gsl_matrix* I = mat_I(n);
  my_gsl_linalg_cholesky_decomp (A);

  return A; // Returns lower tri.
} // So: mvrnorm <- function(M,S,n=nrow(S)) M + chol(S) %*% rnorm(n)

//http://search.cpan.org/dist/Math-GSL/lib/Math/GSL/Randist.pm
gsl_matrix* rnorm(int n, double m, double s, gsl_rng* r) {
  //gsl_rng* r = gsl_rng_alloc (gsl_rng_mt19937);
  gsl_matrix* x = gsl_matrix_alloc(n,1);
  double d;

  for (int i=0; i<n; i++) {
    d = m + gsl_ran_gaussian(r,s);
    gsl_matrix_set (x, i, 0, d);
  }

  return x;
} //tested
