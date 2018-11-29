#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;


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

class TriDiag{
private:
  double *_matrix;
  int _size;
public:
  TriDiag(int size) : _size(size), _matrix(new double[size*size]){
    for (int i = 0; i < _size*_size; i++)
      _matrix[i] = 0;
    for(int i = 0; i < _size*_size; i++){
      set(1, i, i-1);
      set(4, i, i);
      set(1, i, i+1);
    }
    set(2, 0, 0);

  }
  void set(double val, int row, int col){
    if(col > row +1)
      return;
    else if (col < row -1)
      return;
    else if (row < 0)
      return;
    else if (col < 0 )
      return;
    else if (col >= _size)
      return;
    else if( row >= _size)
      return;

    _matrix[_size*row-col] = val;
  }
  ~TriDiag(){ delete [] _matrix;}
  void getVals(int i, int j){
        cout << _matrix[_size*i+j] << '\n';
      }
  void printMatrix(){
    for(int i = 0; i <_size*_size; i++){
        cout << "Matrix at position: " << i << ": " << _matrix[i] << '\n';
    }
  }

};


int main(){
  ifstream f("splinehw.dat");
  string s;
  string b;
  Point a;
  vector<Point> points;
  int count;
  TriDiag t(3);
  t.getVals(1,1);
  t.printMatrix();
  while (getline(f, s)){
    if (count++ > 0){
    istringstream iss(s);
    for(s; iss >> a.x >> a.y; )
      cout << a << '\n';
      points.push_back(a);
    }
    if (s == "")
      break;
  }
  return 0;
}
