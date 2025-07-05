/*
Task description
A non-empty array A consisting of N integers is given. The array contains an odd number of elements, and each element of the array can be paired with another element that has the same value, except for one element that is left unpaired.

For example, in array A such that:

  A[0] = 9  A[1] = 3  A[2] = 9
  A[3] = 3  A[4] = 9  A[5] = 7
  A[6] = 9
the elements at indexes 0 and 2 have value 9,
the elements at indexes 1 and 3 have value 3,
the elements at indexes 4 and 6 have value 9,
the element at index 5 has value 7 and is unpaired.
Write a function:

int solution(vector<int> &A);

that, given an array A consisting of N integers fulfilling the above conditions, returns the value of the unpaired element.

For example, given array A such that:

  A[0] = 9  A[1] = 3  A[2] = 9
  A[3] = 3  A[4] = 9  A[5] = 7
  A[6] = 9
the function should return 7, as explained in the example above.

Write an efficient algorithm for the following assumptions:

N is an odd integer within the range [1..1,000,000];
each element of array A is an integer within the range [1..1,000,000,000];
all but one of the values in A occur an even number of times.
*/

// you can use includes, for example:
// #include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

#include <iostream>
#include <unordered_set>

using namespace std;

int solution(vector<int> &A) {
    // Implement your solution here
    unordered_set<int> intset;
	// prevents rehashing, speeds up by ~0.02 sec
	intset.reserve(A.size());

    for (auto it = A.begin(); it != A.end(); ++it)
    {
        // if (!intset.insert(*it).second)
        //     intset.erase(*it);

		// slightly slower by ~0.005 sec with 2 hash lookups for find and insert 
        if (intset.find(*it) == intset.end())
        	intset.insert(*it);
        else
        	intset.erase(*it);
    }

    // cout << intset.size() << endl;

    unordered_set<int>::iterator it = intset.begin();
    int answer = *it;

    return answer;
}