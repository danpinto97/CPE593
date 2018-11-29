/*
  Author: Daniel Pinto
  Note: I couldn't get it to work the way Prof Kruger wanted
  so I hard coded it manuallly (with my growarray), in one function rather than
  a convexhull class. Hopefully this is still good for something.
  Works with convexhullpoints.dat from session 06.

  References: https://www.geeksforgeeks.org/convex-hull-set-1-jarviss-algorithm-or-wrapping/
  for convex hull/ orientation algorithms
  Joe Puciloski for some help with understanding GrowArrays
*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//g++ -std=c++11 convex_hull.cpp
template <typename T>

class GrowArray {
private:
  	T* data;
  	int used;
  	int capacity;
  	void grow() {
  		capacity = capacity * 2 + 2;
  		T* temp = data;
  		data = new T[capacity];
  		for (int i = 0; i < used; i++)
  			data[i] = temp[i];
  		delete [] temp;
  	}
public:
  	GrowArray() : data(NULL), used(0), capacity(0) {}
  	~GrowArray() {
  		delete [] data;
  	}
  	GrowArray(const GrowArray& orig): data(new T[orig.used]), used(orig.used), capacity(orig.capacity) {
  		for (int i = 0; i < orig.used; i++)
  			data[i] = orig.data[i];
  	}
  	GrowArray& operator =(GrowArray copy) {
  		T* temp = data; data = copy.data; copy.data = temp;
  	}
  	friend ostream& operator <<(ostream& s, const GrowArray& a){
  		for (int i = 0; i < a.used - 1; i++)
  			s << a.data[i] << ",";
  		s << a.data[a.used - 1];
  		return s;
  	}
  	void add(const GrowArray& orig){
  		for(int i = 0; i < orig.used; i++){
  			if (used >= capacity)
  				grow();
  			data[used++] = orig.data[i];
  		}
  }
  void add_front(T orig) {
    if (used >= capacity)
      grow();
    used++;
    for (int i = used; i > 0; i--)
      data[i] = data[i-1];
    data[0] = orig;
  }
  void add_back(T orig) {
    if (used >= capacity)
      grow();
    data[used++] = orig;
  }
  void remove_back(){
    used--;
  }
  void remove_front(){
    used--;
    for (int i = 0; i < used; i++)
      data[i] = data[i+1];
  }
  T get(int pos) const{
    return data[pos];
  }
  int size(){
    return used;
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

int orientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;
    return (val > 0)? 1: 2;
}


// Prints convex hull of a set of n points.
void convexHull(Point points[], int n)
{
    if (n < 3) return;
    GrowArray<Point> hull;
    int l = 0;
    for (int i = 1; i < n; i++)
        if (points[i].x < points[l].x)
            l = i;
    int p = l, q;
    do
    {
        hull.add_back(points[p]);
        q = (p+1)%n;
        for (int i = 0; i < n; i++)
        {
           if (orientation(points[p], points[i], points[q]) == 2)
               q = i;
        }
        p = q;

    } while (p != l);
for (int i = 0; i < hull.size(); i++)
    cout << "(" << hull.get(i).x << ", "
          << hull.get(i).y << ")\n";
}


int main(){

  ifstream infile("convexhullpoints.dat");

  //double a, b;
  GrowArray<Point> points;
  Point a;
  Point p[4] = {};//set size of p manually to match number of points in .dat
  int count = 0;
  while (infile >> a.x >> a.y)//read in points
  {
      points.add_back(a);
      p[count] = a;
      count++;

  }
  int n = sizeof(p)/sizeof(p[0]);
  cout << "Convex hull: \n";
  convexHull(p,n);

  Point pointz[] = {{0, 3}, {2, 2}, {1, 1}, {2, 1},
                  {3, 0}, {0, 0}, {3, 3}};


}
