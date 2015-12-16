#include "my_gsl.h" // print & read matrices / other functions



//lpb(be::Array{Float64,1}) = -be'XXi*be/2s2
double lpb(gsl_matrix* b, gsl_matrix* XXi, double s2) {
  gsl_matrix* bt = mat_t(b);
  gsl_matrix* W = mat_prod( mat_prod(bt,XXi), b);
  gsl_matrix* Wdc = mat_scale(W,1/(-2*s2));
  return gsl_matrix_get(Wdc,0,0);
}

//lps(sig2::Float64) = (a-1)*log(s2)-s2/b 
double lps(double s2, double a, double b) {
  return (a-1)*log(s2)-s2/b;
}

double ll(gsl_matrix* be, double sig2, gsl_matrix* y, gsl_matrix* X) {
  int n = nrow(y);
  int k = ncol(X);
  gsl_matrix* Xb = mat_prod(X,be);
  gsl_matrix* c = mat_sub(y, Xb);
  gsl_matrix* out = mat_add_c(mat_scale(mat_prod(mat_t(c),c),1/sig2),
      n*log(sig2)/-2.0);
  return gsl_matrix_get(out,0,0);
}

gsl_matrix* mvrnorm(gsl_matrix* m, gsl_matrix* cholS) {
  int n = nrow(m);
  gsl_matrix* e = rnorm(n,0,1);
  gsl_matrix* Se = mat_prod( cholS, e ); 
  return mat_add(m, Se);
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
  const gsl_matrix* dat = read_csv(filename,' ');
  int n = nrow(dat);
  int mk = ncol(dat);
  const gsl_matrix* X = mat_get(dat,0,n-1,1,mk-1);
  const gsl_matrix* y = mat_get(dat,0,n-1,0,0);
  int k = ncol(X);

  const gsl_matrix* Xt = mat_t(X);
  const gsl_matrix* XXi = mat_inv(mat_prod(Xt,X));
  const double s2 = 10;
  const double s = 100;
  const double a = 1;
  const double b = 1;
  const gsl_matrix* csb = mat_scale(XXi,4);
  const gsl_matrix* cholS = mat_chol(csb);
  const double css = 1;
  double q;
  
  const gsl_matrix* mle = mat_prod(XXi,mat_prod(Xt,y));
  //print_mat(mle); //correct!

  //gibbs
  int B = 1000;
  int accb = 0;
  int accs = 0;
  gsl_matrix* bb = gsl_matrix_alloc(B,k); gsl_matrix_set_zero(bb);
  gsl_matrix* ss = gsl_matrix_alloc(B,1); gsl_matrix_set_all(ss,1);
  gsl_matrix* candb = gsl_matrix_alloc(k,1);
  gsl_matrix* bcur = gsl_matrix_alloc(k,1);
  double cands;
  double sc = 1;
  gsl_vector_view v;
  bcur = mat_t(mat_row(bb,0));

  for (int b=1; b<B; b++) {
    printf("%d\r",b);
    
    //Set Previous Values:
    //gsl_matrix_set_row(bb,b,&v);
    gsl_matrix_set(ss,b,0,sc);

    //Update beta:
    //candb = mvrnorm(bcur,cholS);
    //q = ll(candb,sc,y,X) - 
    //    ll( bcur,sc,y,X) +
    //    lpb(candb,XXi,sc)-
    //    lpb( bcur,XXi,sc);

    //if (q>log(runif())) {
    //  v = gsl_matrix_column(candb,0);
    //  gsl_matrix_set_col(bcur,0,&v);
    //  accb += 1;
    //}

    //Update s2:
    cands = gsl_matrix_get(rnorm(1,sc,css),0,0);
    if (cands>0) {
      q = ll(bcur,cands,y,X)+lps(cands,a,b)-ll(bcur,sc,y,X)-lps(sc,a,b);
      if (q>log(runif())) {
        sc = cands;
        accs += 1;
      }
    }
  }
  
  print_matrix(bb,"out/bb.dat");
  print_matrix(ss,"out/ss.dat");

  // Free memory:
  gsl_matrix_free(dat);
  gsl_matrix_free(X);
  gsl_matrix_free(y);
  return 0;
}
