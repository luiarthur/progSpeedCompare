#include "my_gsl.h" // print & read matrices / other functions

//lpb(be::Array{Float64,1}) = -be'XXi*be/2s2
double lpb(gsl_matrix* b, gsl_matrix* XXi, double s2) {
}

//lps(sig2::Float64) = (a-1)*log(s2)-s2/b 
double lps(double s2, double a, double b) {
}

double ll(gsl_matrix* be, double sig2, gsl_matrix* y, gsl_matrix* X) {
}

gsl_matrix* mvrnorm(gsl_matrix* m, gsl_matrix* cholS, gsl_rng* r) {
}


int main(int argc, char* argv[]) {
  gsl_rng* r = gsl_rng_alloc (gsl_rng_taus);
  char* filename = "../data/dat.txt";
  int n = countFileRows(filename);
  int k = countFileCols(filename,' ');
  gsl_matrix* M = gsl_matrix_alloc(n,k);

  printf("%d%s%d\n",n,"x",k);

  // Free Memory:
  gsl_matrix_free(M);
  gsl_rng_free(r);

  return 0;
}
