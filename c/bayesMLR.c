#include "my_gsl.h" // print & read matrices / other functions

double ll(gsl_matrix* b, double s2, gsl_matrix* y, gsl_matrix* X) {
  int n = nrow(y);
  int k = ncol(X);
  gsl_matrix* Xb = mat_prod(X,b);
  gsl_matrix* c = mat_sub(y, Xb);
  gsl_matrix* out = mat_add_c(mat_scale(mat_prod(mat_t(c),c),1/s2),
      n*log(s2)/-2.0);
  return gsl_matrix_get(out,0,0);
}

gsl_matrix* mvrnorm(gsl_matrix* m, gsl_matrix* S) {
  int n = nrow(m);
  gsl_matrix* e = rnorm(n,0,1);
  gsl_matrix* Se = mat_prod( mat_chol(S), e );
  return mat_add(m, Se);
}

double gibbs(int* n, int* k, gsl_matrix* mle) {
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
  gsl_matrix* m = read_csv(filename,' '); // my_gsl
  int n = nrow(m);
  int k = ncol(m);

  print_mat(m);
  return 0;
}
