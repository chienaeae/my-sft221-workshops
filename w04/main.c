#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_FACTORIALS 10000
#define NUM_FACTS 100

struct FactorialResults
{
    int results[MAX_FACTORIALS];
    int numResults;
};

int factorial(const int n)
{
    // return (n <= n) ? n * factorial(n - 1) : 1;
    // bug 1: the termination condition (n <= n) is always true.
    // bug 2: factorial(13) exceeds the integer maximun value, should return -1
    if (n >= 13)
    {
        return -1;
    }
    return (n > 1) ? n * factorial(n - 1) : 1; // correct
}

int reduceFactorial(const int n)
{
    // return n / n;
    // bug 1: to divide zero or negative number if give n is zero or negative
    return n > 0 ? (n / n) : 1; // correct
}

// void computeFactorials(struct FactorialResults *results, int numFactorials)
// bug 1: FactorialResults passed by value. changes inslide the function
// will not affect the original value outside of the function
void computeFactorials(struct FactorialResults *results, int numFactorials) // correct
{
    int i;
    for (i = 0; i < numFactorials; i++)
    {
        // results.results[i] = factorial(i);
        // bug 1: results is pointer, not FactorialResults structure.
        // we should use -> to access the member of FactorialResults
        results->results[i] = factorial(i); // correct
    }

    // results.numResults = numFactorials;
    // bug 1: results is pointer, not FactorialResults structure.
    // we should use -> to access the member of FactorialResults
    results->numResults = numFactorials;
}

int main(void)
{
    struct FactorialResults results = {{0}, 0};
    int i;
    // computeFactorials(results, NUM_FACTS);
    // bug 1: computeFactorials accept a FactorialResults pointer as parameter
    computeFactorials(&results, NUM_FACTS); // correct
    for (i = 0; i < NUM_FACTS; i++)
    {
        // results.results[i] = reduceFactorial(results.results[i]);
        // bug 1: reduceFactorial always return 0 or 1. it is meanless here

        // printf("%5d %12f\n", i, results.results[i]);
        // bug 1: format specifies type 'double', but the arguement has type 'int'
        printf("%5d %12d\n", i, results.results[i]); // correct
    }
    return 0;
}
