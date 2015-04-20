#include <stdio.h>
#include <gsl/gsl_linalg.h>

int main(void) {
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

  gsl_matrix_view X = gsl_matrix_view_array(X_dat,10,2);
  gsl_matrix *Xt = gsl_matrix_alloc(2,10);
  gsl_matrix_transpose_memcpy(Xt,&X.matrix);
  gsl_vector_view y = gsl_vector_view_array(y_dat,10);
  gsl_matrix *b = gsl_matrix_alloc(10,1);
  
  //gsl_linalg_QR_solve(
  //b =    1,3 
  //    .606,2.97
  gsl_matrix_fprintf(stdout,b,"%g");
  //gsl_matrix_fprintf(stdout,Xt,"%g");
  gsl_matrix_free(b);
  return 0;
}
