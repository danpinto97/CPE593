/*
  Author: Daniel Pinto

  Sources: https://www.geeksforgeeks.org/segmented-sieve/
           https://primesieve.org/segmented_sieve.html
   -- segmented sieve
  "Use Simple Sieve to find all primes upto square root of ‘n’ and store these primes in an array “prime[]”. Store the found primes in an array ‘prime[]’.
    We need all primes in range [0..n-1]. We divide this range in different segments such that size of every segment is at-most √n
    Do following for every segment [low..high]
        Create an array mark[high-low+1]. Here we need only O(x) space where x is number of elements in given range.
        Iterate through all primes found in step 1. For every prime, mark its multiples in given range [low..high]."
  and help from Joe Puciloski
  https://primes.utm.edu/howmany.html to check answers
*/

#include <iostream>
#include <cmath>
#include <vector>
#include "bitvec.hh"
using namespace std;

uint64_t segmented_sieve(uint64_t a, uint64_t b){
    uint64_t a_size = sqrt(b);
    int prime_count = 0;
    uint64_t primes = 0;
    //simple sieve
    vector<bool> sieve(a_size, true);
    vector<int> simple;
    sieve[0], sieve[1] = false;
    for (uint64_t i = 4; i <= a_size; i += 2)
    	sieve[i] = false;
      //set all even numbers to false and the rest are true
    for (uint64_t i = 2; i <= a_size; i++){
      //go from 2 to sqrt of max and check if true at that number i
        if (sieve[i]){
            if (i>=a)
                prime_count++;
            simple.push_back(i);
            //store all primes
            for (uint64_t j = i*i; j <= a_size; j += 2*i)
                sieve[j] = false;   //num is composite
            primes++;
        }
    }
    sieve.clear();
    //finish normal sieve to sqrt(n)
    uint64_t lo = a;
    //low = min passed in
    if (lo < a_size)
    	lo = a_size+1;
    uint64_t hi = lo+a_size;
    //high is equal to the min + sqrt(max)
    if (hi > b)
    	hi = b;

    while (lo < b){
    	vector<bool> seg(hi-lo+1, true);
        for (uint64_t i = 0; i < primes; i++){
            uint64_t first_mult = (lo/simple[i])*simple[i];
            if (first_mult<lo)
                first_mult+=simple[i];
            for (uint64_t j = first_mult; j <= hi; j += simple[i])
                seg[j-lo] = false; //num is composite
        }
        for (uint64_t i = lo; i <= hi; i++){
            if (seg[i-lo] && i>=a){
                prime_count++;
            }
        }
        lo += a_size+1;
        hi += a_size+1;
        if (hi >= b)
            hi = b;
    }
    return prime_count;
}



int main(){
  unsigned long long min, max;
  cout << "Enter the min and max value to search between separated by a space ";
  cin >> min >> max;
  cout << segmented_sieve(min, max) << '\n';
  return 0;
}
