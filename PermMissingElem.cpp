/*
Task description
An array A consisting of N different integers is given. The array contains integers in the range [1..(N + 1)], which means that exactly one element is missing.

Your goal is to find that missing element.

Write a function:

int solution(vector<int> &A);

that, given an array A, returns the value of the missing element.

For example, given array A such that:

  A[0] = 2
  A[1] = 3
  A[2] = 1
  A[3] = 5
the function should return 4, as it is the missing element.

Write an efficient algorithm for the following assumptions:

N is an integer within the range [0..100,000];
the elements of A are all distinct;
each element of array A is an integer within the range [1..(N + 1)].
*/

// you can use includes, for example:
// #include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

#include <unordered_set>
#include <iostream>

int solution(vector<int> &A) {
    // Implement your solution here

    unordered_set<int> elements;

	// populate elements set with integers in range [1, N+1] where N is size of vector A
    for (int it = 1; it <= A.size() + 1; ++it)
    {
        elements.insert(it);
    }

	// empty elements set of integers in vector A
    for (int num : A)
    {
        elements.erase(num);
    }

    auto it = elements.begin();
    return *it;
}