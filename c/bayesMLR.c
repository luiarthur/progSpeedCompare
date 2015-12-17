#include "my_gsl.h" // print & read matrices / other functions

double lpb(gsl_vector* b, gsl_matrix* XXi, double s2) {
  // b' XXi b / -(2*s2)
  int n = b->size;
  double out = 0;
  double rowSum;

  for (int i=0; i<n; i++) {
    rowSum = 0;
    for (int j=0; j<n; j++) {
      rowSum += gsl_vector_get(b,j) * gsl_matrix_get(XXi,i,j);
    }
    out += rowSum * gsl_vector_get(b,i);
  }

  out = out / -(2*s2);

  return out;
}

double lps(double s2, double a, double b) {
  return (a-1) * log(s2) - s2/b;
}

double ll(gsl_vector* b, double s2, gsl_vector* y, gsl_matrix* X) {
  // c = y-X*be
  // c'c/(-2sig2)-n*log(sig2)/2 
  double out = 0;
  double yi;
  double Xbi;
  int n = b->size;

  for (int i=0; i<n; i++) {
    Xbi = 0;
    for (int j=0; j<n; j++) {
      Xbi += gsl_matrix_get(X,i,j) * gsl_vector_get(b,j);
    }
    yi = gsl_vector_get(y,i);
    out += pow(yi - Xbi,2);
  }
  
  out = out / (-2*s2) - n * log(s2) / 2;
  return out;
}

int main(int argc, char* argv[]) {
  // chol
  gsl_rng* r = gsl_rng_alloc(gsl_rng_taus);
  char* filename = "../data/dat.txt";
  int n = countFileRows(filename);
  int k1 = countFileCols(filename,' ');
  int k = k1 - 1;

  gsl_matrix* M = gsl_matrix_alloc(n,k1);
  gsl_matrix* X = gsl_matrix_alloc(n,k);
  gsl_vector* y = gsl_vector_alloc(n);
  gsl_matrix* csb = gsl_matrix_alloc(k,k);
  gsl_matrix* cholS = gsl_matrix_alloc(k,k);

  read_csv(filename, M);
  mat_sub(M,0,n-1,1,k,X);
  gsl_matrix_get_col(y,M,0);

  xxi_m(X,csb);
  gsl_matrix_scale(csb,4);

  int B = 100;
  int acc_b = 0;
  int acc_s = 0;
  gsl_matrix* bb = gsl_matrix_alloc(B,k);
  gsl_vector* ss = gsl_vector_alloc(B);
  gsl_vector* candb = gsl_vector_alloc(k);

  for (int b=1; b<B; b++) {
    // update beta
    //mvrnorm(m,chols,r,v)

    // update s2

  }


  // Free Memory:
  gsl_matrix_free(cholS);
  gsl_vector_free(candb);
  gsl_vector_free(ss);
  gsl_matrix_free(bb);
  gsl_matrix_free(csb);
  gsl_vector_free(y);
  gsl_matrix_free(X);
  gsl_matrix_free(M);
  gsl_rng_free(r);

  return 0;
}
