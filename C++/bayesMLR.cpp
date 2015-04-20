#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

const double pi  =3.141592653589793238462;

double runif(){
  return (double) rand() / (RAND_MAX); 
}

double rnorm(double mu, double sd) {
  double u1 = runif();
  double u2 = runif();
  double rnorm01 = sqrt(-2.0 * log(u1)) * sin(2.0*pi*u2);
  return mu + sd * rnorm01;
}



int main(int argc, char** argv) {
  int n,k;  // nrow(X),ncol(X)
  mat z,X,y,mle;

  z.load("../data/dat.txt");
  n = z.n_rows;
  k = z.n_cols-1;

  y = z.col(0);
  X = z.cols(1,k); // columns 2 to k+1 of z
  mle = (X.t()*X).i() * X.t() * y;

  


  cout << "MLE: \n" << mle << endl;
  
  return 0;
}
