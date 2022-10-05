/*
 * TODO: remove and replace this file header comment
 * This is a .cpp file you will edit and turn in.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include "console.h"
#include <iostream>
#include "testing/SimpleTest.h"
#include <cmath>
using namespace std;

/* This function takes one argument `n` and calculates the sum
 * of all proper divisors of `n` excluding itself. To find divisors
 * a loop iterates over all numbers from 1 to n-1, testing for a
 * zero remainder from the division.
 *
 * Note: long is a C++ type is a variant of int that allows for a
 * larger range of values. For all intents and purposes, you can
 * treat it like you would an int.
 */
long divisorSum(long n) {
    long total = 0;
    for (long divisor = 1; divisor < n; divisor++) {
        if (n % divisor == 0) {
            total += divisor;
        }
    }
    return total;
}

/* This function takes one argument `n` and returns a boolean
 * (true/false) value indicating whether or not `n` is perfect.
 * A perfect number is a non-zero positive number whose sum
 * of its proper divisors is equal to itself.
 */
bool isPerfect(long n) {
    return (n != 0) && (n == divisorSum(n));
}

/* This function does an exhaustive search for perfect numbers.
 * It takes one argument `stop` and searches the range 1 to `stop`,
 * checking each number to see whether it is perfect and if so,
 * printing it to the console.
 */
void findPerfects(long stop) {
    for (long num = 1; num < stop; num++) {
        if (isPerfect(num)) {
            cout << "Found perfect number: " << num << endl;
        }
        if (num % 10000 == 0) cout << "." << flush; // progress bar
    }
    cout << endl << "Done searching up to " << stop << endl;
}

/* This function takes one argument `n` and calculates the sum
 * of all proper divisors of `n` which is smaller than sqrt(n).
 * To find divisors a loop iterates over all numbers from 1 to
 * sqrt(n), testing for a zero remainder from the division.
 */
long smarterSum(long n) {
    long total = 0;
    for (long divisor = 1; divisor <= sqrt(n); divisor++) {
        if (n % divisor == 0 && n != 1) {
            total += divisor;
            if (divisor != 1 && divisor != sqrt(n) ) {
                total += (n / divisor);
            }
        }
    }
    return total;
}

/* This function takes one argument `n` and returns a boolean
 * (true/false) value indicating whether or not `n` is perfect.
 * A perfect number is a non-zero positive number whose sum
 * of its proper divisors is equal to itself.
 */
bool isPerfectSmarter(long n) {
    return (n != 0) && (n == smarterSum(n));
}

/* This function does an exhaustive search for perfect numbers.
 * It takes one argument `stop` and searches the range 1 to `stop`,
 * checking each number to see whether it is perfect and if so,
 * printing it to the console.
 */
void findPerfectsSmarter(long stop) {
    for (long num = 1; num < stop; num++) {
        if (isPerfectSmarter(num)) {
            cout << "Found perfect number: " << num << endl;
        }
        if (num % 10000 == 0) cout << "." << flush; // progress bar
    }
    cout << endl << "Done searching up to " << stop << endl;
}

/* This function is using Euclid's approach to find perfect numbers.
 * It takes one argument `n`, and a loop iterates over from exp k=2 to
 * find the ith perfect number. It stops when i = n, and return nth
 * perfect number.
 */
long findNthPerfectEuclid(long n) {
    int k = 2;
    int i = 0;
    long m = 0;
    long perfectNum = 0;
    while (i < n) {
        m = pow(2, k) - 1;
        if(divisorSum(m) == 1){
            perfectNum = m * pow(2, (k - 1));
            i++;
        }
        k++;
    }
    return perfectNum;
}


/* * * * * * Test Cases * * * * * */

/* Note: Do not add or remove any of the PROVIDED_TEST tests.
 * You should add your own STUDENT_TEST tests below the
 * provided tests.
 */

PROVIDED_TEST("Confirm divisorSum of small inputs") {
    EXPECT_EQUAL(divisorSum(1), 0);
    EXPECT_EQUAL(divisorSum(6), 6);
    EXPECT_EQUAL(divisorSum(12), 16);
}

PROVIDED_TEST("Confirm 6 and 28 are perfect") {
    EXPECT(isPerfect(6));
    EXPECT(isPerfect(28));
}

PROVIDED_TEST("Confirm 12 and 98765 are not perfect") {
    EXPECT(!isPerfect(12));
    EXPECT(!isPerfect(98765));
}

PROVIDED_TEST("Test oddballs: 0 and 1 are not perfect") {
    EXPECT(!isPerfect(0));
    EXPECT(!isPerfect(1));
}

PROVIDED_TEST("Confirm 33550336 is perfect") {
    EXPECT(isPerfect(33550336));
}

PROVIDED_TEST("Time trials of findPerfects on doubling input sizes") {
    TIME_OPERATION(10000, findPerfects(10000));
    TIME_OPERATION(20000, findPerfects(20000));
    TIME_OPERATION(40000, findPerfects(40000));
}

// TODO: add your student test cases here

STUDENT_TEST("Test My Time trials of findPerfects on doubling input sizes") {
    TIME_OPERATION(32500, findPerfects(32500));
    TIME_OPERATION(65000, findPerfects(65000));
    TIME_OPERATION(130000, findPerfects(130000));
    TIME_OPERATION(260000, findPerfects(260000));
}

STUDENT_TEST("Confirm -6 and -28 are perfect") {
    EXPECT(isPerfect(-6));
    EXPECT(isPerfect(-28));
}

STUDENT_TEST("Confirm 8 or 28 is perfect, when total = 1 in 'divisorSum' ") {
    EXPECT(isPerfect(8));
    EXPECT(isPerfect(28));
}

STUDENT_TEST("Confirm smarterSum is equal to 0 of small inputs 1") {
    EXPECT_EQUAL(smarterSum(1), 0);
}

STUDENT_TEST("Confirm smarterSum is equal to 25 of small inputs 25") {
    EXPECT_EQUAL(smarterSum(25), 25);
}

STUDENT_TEST("Confirm smarterSum is equal to 8 of small inputs 49") {
    EXPECT_EQUAL(smarterSum(49), 8);
}

STUDENT_TEST("Test My Time trials of findPerfectsSmarter on doubling input sizes") {
    TIME_OPERATION(750000, findPerfectsSmarter(750000));
    TIME_OPERATION(1500000, findPerfectsSmarter(1500000));
    TIME_OPERATION(3000000, findPerfectsSmarter(3000000));
    TIME_OPERATION(6000000, findPerfectsSmarter(6000000));
}

STUDENT_TEST("Confirm findNthPerfectEuclid of small inputs") {
    EXPECT_EQUAL(findNthPerfectEuclid(2), 28);
    EXPECT_EQUAL(findNthPerfectEuclid(3), 496);
    EXPECT(isPerfect(findNthPerfectEuclid(4)));
    EXPECT(isPerfect(findNthPerfectEuclid(5)));
}
