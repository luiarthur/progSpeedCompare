#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

const double pi  =3.141592653589793238462;
int n,k;  // nrow(X),ncol(X)
mat z,X,y,XXi,Xt;
const double a=1;
const double b=1;
const int B=pow(10,5);
//const int B=pow(10,2);
const double s2 = 10;

double runif(){
  return (double) rand() / (RAND_MAX); 
}

double rnorm(double mu, double sd) {
  double u1 = runif();
  double u2 = runif();
  double rnorm01 = sqrt(-2.0 * log(u1)) * sin(2.0*pi*u2);

  return mu + sd * rnorm01;
}

mat rnorms(int n) {
  mat out(n,1);
  for (int i=0; i<n; i++) {
    out(i,0) = rnorm(0,1);
  }
  return out;
}


double ll(mat be, double sig2) {
  mat c, out;

  c = y-X*be;
  out = c.t() * c / (-2*sig2);
  
  return as_scalar(out);
}

double lpb(mat be) {
  return as_scalar(-s2/2 * be.t() * XXi * be);
}

double lps(double sig2) {
  return (a-1) * log(sig2) - sig2/b;
}

mat mvrnorm(mat M, mat S) {
  int n = M.n_rows;
  mat e = rnorms(n);
  return M + chol(S).t()*e;
}
// mvrnorm <- function(M,S,n=nrow(S)) M + t(chol(S)) %*% rnorm(n)


int main(int argc, char** argv) {
  int i,j;
  mat mle;

  //posteriors:
  mat bb; 
  mat ss;

  // candidate sigma:
  mat csb;
  const double css = 1;

  //candidate values:
  mat candb;
  double cands;
  
  //acceptance rates:
  int accb = 0;
  int accs = 0;

  //metropolis ratio:
  double q;

  //current vals:
  mat bc;
  double sc;


  z.load("../data/dat.txt");
  n = z.n_rows;
  k = z.n_cols-1;

  y = z.col(0);
  X = z.cols(1,k); // columns 2 to k+1 of z
  Xt = X.t();
  XXi = (Xt*X).i();
  csb = 4*XXi;
  mle = XXi * Xt * y;
  
  bb.set_size(B,k);
  ss.set_size(B,1);
  bb.zeros();
  ss.ones();

  for (int i=1; i<B; i++) {
    // Set Initial Values:
    bb.row(i) = bb.row(i-1); 
    ss.row(i) = ss.row(i-1); 

    bc = bb.row(i).t();
    sc = as_scalar(ss.row(i));

    //Update Beta:
    candb = mvrnorm(bb.row(i).t(),csb);
    q = ll(candb,sc)+lpb(candb) -ll(bc,sc)-lpb(bc);
    if (q>log(runif())) {
      bc = candb;
      bb.row(i) = bc.t();
      accb++;
    }

    //Update sigma2:
    cands = rnorm(sc,css);
    if (cands>0){
      q = ll(bc,cands)+lps(cands) - ll(bc,sc)-lps(sc);
      if (q>log(runif())) {
        ss.row(i) = cands;
        accs++;
      }
    }
  }



  cout <<"B: "<<B<<endl;
  cout << "MLE: \n" << mle << endl;
  cout << "Beta Acceptance:   "<< 100*accb/B <<"%"<<endl;
  cout << "Sigma2 Acceptance: "<< 100*accs/B <<"%"<<endl;
  cout << "Posterior Means Beta: \n" << mle << endl;
  cout <<mean(bb.rows(90000-1,100000-1)).t()<<endl;
  cout << "Posterior Mean Sigma2: \n" << mle << endl;
  cout <<mean(ss.rows(90000-1,100000-1)).t()<<endl;

  return 0;
}
