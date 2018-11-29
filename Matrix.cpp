#include <iostream>
using namespace std;

class Matrix {
private:
   double* m;
   int rows, cols;
   //This one does not initialize
   Matrix(int r, int c, char*) : rows(r), cols(c), m(new double[r*c]) {}
public:
   Matrix(int r, int c, double val = 0) : rows(r), cols(c), m(new double[rows*cols]) {
      for(int i = 0; i < rows*cols; ++i)
         m[i] = val;
   }

   ~Matrix() { delete [] m; }

   Matrix(const Matrix& orig); //TODO copy constructor
   Matrix& operator=(const Matrix& orig); //TODO
   Matrix(Matrix&& orig) : rows(orig.rows), cols(orig.cols), m(orig.m) { // Move constructor
      orig.m = nullptr;
   }

   friend Matrix operator+(const Matrix& a, const Matrix& b) {
      if(a.rows != b.rows || a.cols != b.cols)
         throw "Bad size";
      Matrix ans(a.rows, a.cols);
      // for(int i = 0; i < a.rows; ++i)
      //    for(int j = 0; j < a.cols; ++j)
      //       ans.m[i*cols + j] = a.m[i*cols+j] + b.m[i*cols+j];

      //More effiecent for addition : slightly faster
      for(int i = 0; i < a.rows*a.cols; ++i)
         ans.m[i] = a.m[i] + b.m[i];

      return ans;
   }

   friend Matrix operator-(const Matrix& a, const Matrix& b) {
      if(a.rows != b.rows || a.cols != b.cols)
         throw "Bad size";

      Matrix ans(a.rows, a.cols);
      for(int i = 0; i < a.rows*a.cols; ++i)
         ans.m[i] = a.m[i] - b.m[i];

      return ans;
   }

   friend Matrix operator*(const Matrix& a, const Matrix &b) {
      if(a.cols != b.rows)
         throw "Bad size";

      Matrix ans(a.rows, b.cols);
      for(int k = 0; k < a.rows; k++) {
         for(int j = 0; j < b.cols; j++) {
            double dot = 0;
            for(int i = 0; i < a.cols; i++)
               dot += a(k,i) * b(i,j);
            ans(k,j) = dot;
         }
      }
      return ans;
   }

};

int main() {
   Matrix m1(3,4,1);
   Matrix m2(3,4,2);
   Matrix m3 = m1 + m2;
}
