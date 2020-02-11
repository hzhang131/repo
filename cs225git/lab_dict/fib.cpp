/**
 * @file fib.cpp
 * Contains Fibonacci-number generating functions both utilizing and not
 * utilizing memoization.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "fib.h"

#include <map>

using std::map;



/**
 * Calculates the nth Fibonacci number where the zeroth is defined to be
 * 0.
 * @param n Which number to generate.
 * @return The nth Fibonacci number.
 */
unsigned long fib(unsigned long n)
{
    /* Your code goes here! */
    unsigned long res = 0;
    if (n == 0) return 0;
    if (n == 1) return 1;
    else res = fib(n-1) + fib(n-2);
    return res;
}

/**
 * Calculates the nth Fibonacci number where the zeroth is defined to be
 * 0. This version utilizes memoization.
 * @param n Which number to generate.
 * @return The nth Fibonacci number.
 */
unsigned long memoized_fib(unsigned long n)
{
    static map<unsigned long, unsigned long> look_up = {
        {0, 0}, {1,1}
    };
    /* Your code goes here! */
    unsigned long res = 0;
    if (look_up.find(n) != look_up.end()){
        return look_up[n];
    }
    else res = memoized_fib(n-1) + memoized_fib(n-2);
    return res;
}
