/*
  Author: Daniel Pinto
  Sources: https://stackoverflow.com/questions/9330915/number-of-combinations-n-choose-r-in-c
           http://programminggenin.blogspot.com/2013/01/memoization-in-c.html

*/

#include <iostream>
#include <random>
using namespace std;

//Tried using memoization with factorials; didn't work as well
static unsigned long long memo_factorials[500] = {0};
unsigned long long factorial(unsigned long long n)
{
  if (memo_factorials[n] != 0)
    return memo_factorials[n];
  else
    if (n == 0)
      return 1;
  return memo_factorials[n] = (factorial(n - 1) * n);
}

unsigned long long memo_choose_factorial(unsigned long long n, unsigned long long r){
  return ((factorial(n)/(factorial(r)*factorial(n-r))));
}
//------------------------------------------------------------------------------

unsigned long long memo_choose(int n, int r){
  static unsigned long long memo_matrix[500][500] = {0};
  if (r > n) return 0;
  if (r == 0 || n == 0) return 1;
  if (memo_matrix[n][r] != 0)
    return memo_matrix[n][r];
  return memo_matrix[n][r] = memo_choose(n-1,r-1) + memo_choose(n-1,r);
}

unsigned long long regular_choose(unsigned long long n, unsigned long long r) {
  if (r > n) return 0;
  if (2*r > n) r = n-r;
  if (r == 0) return 1;
    int result = n;
    for (int i = 2; i <= r; ++i){
        result *= (n-i+1);
        result /= i;
      }
      return result;
    }

int main() {
  int numTrials = 100000000;
	default_random_engine generator;
	uniform_int_distribution<int> distribution(0,500);
  for (int i = 0; i < numTrials; i++) {
		int n = distribution(generator);
		uniform_int_distribution<int> rdist(0,n);
		int r = rdist(generator);
    memo_choose(n,r);
	}
}
/*
Results from timing memo_choose()
real	0m2.844s
user	0m2.839s
sys	0m0.004s
*/

/*
Results from timing regular_choose()
real	0m2.530s
user	0m2.530s
sys	0m0.000s
*/

/*
So I found the regular_choose function to be faster. However, that function is
not recursive. I think that if I wrote it recursively without memoization, it
would be way slower.
*/
