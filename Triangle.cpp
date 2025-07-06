/*
Task description
An array A consisting of N integers is given. A triplet (P, Q, R) is triangular if 0 ≤ P < Q < R < N and:

A[P] + A[Q] > A[R],
A[Q] + A[R] > A[P],
A[R] + A[P] > A[Q].
For example, consider array A such that:

  A[0] = 10    A[1] = 2    A[2] = 5
  A[3] = 1     A[4] = 8    A[5] = 20
Triplet (0, 2, 4) is triangular.

Write a function:

int solution(vector<int> &A);

that, given an array A consisting of N integers, returns 1 if there exists a triangular triplet for this array and returns 0 otherwise.

For example, given array A such that:

  A[0] = 10    A[1] = 2    A[2] = 5
  A[3] = 1     A[4] = 8    A[5] = 20
the function should return 1, as explained above. Given array A such that:

  A[0] = 10    A[1] = 50    A[2] = 5
  A[3] = 1
the function should return 0.

Write an efficient algorithm for the following assumptions:

N is an integer within the range [0..100,000];
each element of array A is an integer within the range [−2,147,483,648..2,147,483,647].
*/

// you can use includes, for example:
// #include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

#include <algorithm>
#include <vector>
#include <iostream>
// #include <string>

using namespace std;

int solution(vector<int> &A) {
    // Implement your solution here

    if (A.size() < 3)
    {
        return 0;
    }

    // cout << A[0] << endl;
    sort(A.begin(), A.end());
    // cout << A[0] << endl;

	// long int instead of int to prevent overflow from adding sides
    long int first = A[0];
    long int second = A[1];
    long int third = A[2];
    bool side1 = first > 0;
    bool side2 = second > 0;
    bool side3 = third > 0;
    bool flag1 = (first + second) > third;
    // cout << "((first + second) > third)" << flag1 << endl;
    bool flag2 = (first + third) > second;
    // cout << "(first + third) > second)" << flag2 << endl;
    bool flag3 = (second + third) > first;

    if (side1 && side2 && side3 && flag1 && flag2 && flag3)
    {
        return 1;
    }
    
    if (A.size() == 3)
    {
        return 0;
    }

    for (auto it = A.begin() + 3; it != A.end(); ++it)
    {
        first = second;
        second = third;
        third = *it;
        
        side3 = third > 0;
        // cout << "first: " << first << " second: " << second;
        // cout << " third: " << third << endl;
        flag1 = (first + second) > third;
        // cout << "((first + second) > third)" << flag1 << endl;
        flag2 = (first + third) > second;
        // cout << "(first + third) > second)" << flag2 << endl;
        flag3 = (second + third) > first;
        // cout << "((first + second) > third)" << flag3 << endl;

        if (side3 && flag1 && flag2 && flag3)
        {
            return 1;
        }
    }

    return 0;
}