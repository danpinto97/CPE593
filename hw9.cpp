#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;

/*

This code solves the system Ku = f by gaussian elimination.
This particular algorithm is often referred to as the 'Thomas Algorithm'.

K is a tridiagonal matrix:

    K =     [   \   \   \       ]
            |    \   \   \      ]
            |     a   b   c     ]
            |      \   \   \    ]
            |       \   \   \   ]

    Where,
            a: lower diagonal
            b: main diagonal
            c: upper diagonal
            f: RHS or the input vector
            x: solution vector
*/

void print_vector(vector<double> & v);

vector<double> tridiagonal_solver(vector<double> & a, vector<double> & b, vector<double> & c, vector<double> & f);

int main(){

    int n;
    cout << "\nNumber of grid points: ";
    cin >> n; cout << endl;

    double h = 1/(double(n)+1);

    vector<double> a, b, c, f, u;

// Constructing diagonals of K and vector f

    for(int i=0; i<n; i++){
        b.push_back(2/pow(h,2));
        f.push_back(1);
    }
    for(int i=0; i<n-1; i++){
        a.push_back(-1/pow(h,2));
        c.push_back(-1/pow(h,2));
    }

// Solving the system Ku = f

    u = tridiagonal_solver(a, b, c, f);
    print_vector(u);
    return 0;
}

// Printing vectors
void print_vector(vector<double> & v){
    cout<<endl;
    for(int i=0; i<v.size(); i++){
            cout << setprecision(3) << setw(5) << v[i] << endl;
    }
    cout<<endl;
}

// Solving tridiagonal matrices
vector<double> tridiagonal_solver(vector<double> & a, vector<double> & b, vector<double> & c, vector<double> & f){

    int n = f.size();
    vector<double> x(n);

    for(int i=1; i<n; i++){

        double m = a[i-1]/b[i-1];
        b[i] -= m*c[i-1];
        f[i] -= m*f[i-1];
    }
    // solve for last x value
    x[n-1] = f[n-1]/b[n-1];

    // solve for remaining x values by back substitution
    for(int i=n-2; i >= 0; i--)
        x[i] = (f[i]- c[i]*x[i+1])/b[i];

    return x;

}
