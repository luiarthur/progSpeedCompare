#include "my_gsl.h" // print & read matrices / other functions

double ll(gsl_matrix* b, double s2, gsl_matrix* y, gsl_matrix* X) {
  int k = nrow(&b);
  gsl_matrix* c = gsl_matrix_alloc(b,1);
  gsl_matrix* out = gsl_matrix_alloc(b,1);

  //c = y - X*b;
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
  gsl_matrix m = read_csv(filename,' '); // my_gsl
  printf("%d%s%d\n",nrow(&m),"x",ncol(&m)); // my_gsl
  printmatrix(m,"fout.txt"); // my_gsl

  gsl_matrix a = read_csv("tmp/a.dat",' ');
  gsl_matrix b = read_csv("tmp/b.dat",' ');
  //gsl_matrix c = prod(a,b);
  //printmatrix(c,"f2.txt");
  return 0;
}
