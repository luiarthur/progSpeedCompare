#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main(int argc, char** argv) {
  mat A = randu<mat>(4,5);
  mat B = randu<mat>(4,5);
  cout << A*B.t() << endl;
  return 0;
}

/*
#include <cstdlib>
#include <cmath>
#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
#include <ctime>
#include <time.h>
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

mat readFile(string file) {
  in.open(file);

}
*/
