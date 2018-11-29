#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

//template <typename T>
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
      Matrix ans(a.rows, a.cols, "internal");
      // for(int i = 0; i < a.rows; ++i)
      //    for(int j = 0; j < a.cols; ++j)
      //       ans.m[i*cols + j] = a.m[i*cols+j] + b.m[i*cols+j];

      //More effiecent for addition : slightly faster
      for(int i = 0; i < a.rows*a.cols; ++i)
         ans.m[i] = a.m[i] + b.m[i];

      return ans;
   }

};

class Point{
public:
  double x, y;
  Point(): x(0), y(0){}
  Point(double x, double y) : x(x), y(y){}
  friend ostream& operator <<(ostream& s, const Point& a){
    s << '(' << a.x << ", " << a.y << ')';
    return s;
  }
  ~Point(){}
};

int main(){
  ifstream f("splinehw.dat");
  string s;
  string b;
  Point a;
  GrowArray<Point> points;
  int count;
  while (getline(f, s)){
    if (count++ > 0){
    istringstream iss(s);
    for(s; iss >> a.x >> a.y; )
      cout << a << '\n';
      points.add_back(a);
    }
    if (s == "")
      break;
  }
  cout << points;
  return 0;
}
