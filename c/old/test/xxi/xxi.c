//https://www.gnu.org/software/gsl/manual/html_node/Matrices.html
//https://www.gnu.org/software/gsl/manual/gsl-ref_14.html
//http://search.cpan.org/~dsth/Math-GSL-Linalg-SVD-0.0.2/lib/Math/GSL/Linalg/SVD.pm#set_matrix

#include <stdio.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_linalg.h>

gsl_vector_view vec (double* x, int n) {
  return gsl_vector_view_array(x,n);
}

gsl_matrix_view mat (double* x, int n, int k) {
  return gsl_matrix_view_array(x,n,k);
}

void t (gsl_matrix* x, gsl_matrix* xt) {
  gsl_matrix_transpose_memcpy(x,xt);
}

void inv (gsl_matrix* x, gsl_matrix* xi, int n) {
  gsl_permutation *P = gsl_permutation_alloc(n);
  gsl_matrix*  A = gsl_matrix_alloc(n,n);
  // set A???
  int s;

  gsl_linalg_LU_decomp(A,P,&s);
  gsl_linalg_LU_invert(A,P,xi); // Key step!
  
  gsl_matrix_free(A);
  gsl_permutation_free(P);
}

int main(void) {
  int n = 10;
  int k = 2;
  int s;
  gsl_permutation *p = gsl_permutation_alloc(n);

  double X_dat[] = {1,  0.84308968,
                    1,  0.36957876,
                    1, -0.95139704,
                    1, -0.30502312,
                    1,  0.42333452,
                    1, -0.96157118,
                    1, -0.51633551,
                    1, -1.24697192,
                    1, -0.31351990,
                    1,  0.06970609};

  double y_dat[] = { 2.3196663,
                     2.1910086,
                    -3.6330834,
                    -1.4949922,
                     2.3545365,
                    -1.2658993,
                    -1.2124306,
                    -2.9546590,
                     1.1322889,
                     0.9408923};


  gsl_vector_view y = vec(y_dat,n);
  gsl_matrix_view X = mat(X_dat,n,k);
  //gsl_vector_fprintf(stdout,y,"%g");

  gsl_matrix *Xt  = gsl_matrix_alloc(k,n);
  t(Xt,&X.matrix);
  
  gsl_matrix_fprintf(stdout,Xt,"%g");
  gsl_matrix_fprintf(stdout,&X.matrix,"%g");

  /*
  gsl_matrix *XX  = gsl_matrix_calloc(k,k);
  gsl_matrix *XXi = gsl_matrix_calloc(k,k);

  gsl_blas_dgemm(CblasNoTrans,CblasNoTrans,
                 1.0,&Xt.matrix,&X.matrix,
                 0.0,&XX.matrix);

  gsl_linalg_LU_decomp (&XX.matrix,p,&s);
  gsl_linalg_LU_invert (&XX.matrix,p,XXi);

  //gsl_matrix *b = gsl_matrix_alloc(n,1);
  gsl_vector *b = gsl_vector_calloc(n);
  gsl_blas_dgemm(CblasNoTrans,CblasNoTrans,
                 1.0,&XXi.matrix,&X.matrix,
                 0.0,&b.vector);
  
  
  //gsl_linalg_QR_solve(
  //b =    1,3 
  //    .606,2.97
  //gsl_matrix_fprintf(stdout,b,"%g");
  //gsl_matrix_fprintf(stdout,Xt,"%g");
  //gsl_matrix_free(b);
  gsl_vector_free(b);
  */
  return 0;
}
