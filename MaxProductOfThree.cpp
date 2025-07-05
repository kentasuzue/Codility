/*
Task description
A non-empty array A consisting of N integers is given. The product of triplet (P, Q, R) equates to A[P] * A[Q] * A[R] (0 ≤ P < Q < R < N).

For example, array A such that:

  A[0] = -3
  A[1] = 1
  A[2] = 2
  A[3] = -2
  A[4] = 5
  A[5] = 6
contains the following example triplets:

(0, 1, 2), product is −3 * 1 * 2 = −6
(1, 2, 4), product is 1 * 2 * 5 = 10
(2, 4, 5), product is 2 * 5 * 6 = 60
Your goal is to find the maximal product of any triplet.

Write a function:

int solution(vector<int> &A);

that, given a non-empty array A, returns the value of the maximal product of any triplet.

For example, given array A such that:

  A[0] = -3
  A[1] = 1
  A[2] = 2
  A[3] = -2
  A[4] = 5
  A[5] = 6
the function should return 60, as the product of triplet (2, 4, 5) is maximal.

Write an efficient algorithm for the following assumptions:

N is an integer within the range [3..100,000];
each element of array A is an integer within the range [−1,000..1,000].
*/

// you can use includes, for example:
// #include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int solution(vector<int> &A) {
    // Implement your solution here

    vector<int> heappos;
    vector<int> heapneg;
    vector<int> heapnegflip;
    vector<int> heapposflip;

    for (int num : A)
    {
        if (num > 0)
        {
            // since C++ heap is max heap, positive numbers need sign flip
            // so that later heap sort will find lowest magnitude positive numbers
            heappos.push_back(num);
            // positive numbers are stored in heapposflip heap as negative numbers
            heapposflip.push_back(-num);            
        }
        else if (num < 0)
        {
            // since C++ heap is max heap, negative numbers need sign flip
            // so that later heap sort will find largest magnitude negative numbers
            heapneg.push_back(num);  
            // negative numbers are stored in heapnegflip heap as positive numbers
            heapnegflip.push_back(-num);
        }
    }

    // if enough zeros were thrown away, then the remaining integers
    // are too few to have a nonzero product
    if (heappos.size() + heapneg.size() < 3)
    {
        return 0;
    }

    bool zeroflag{false};
    // if the sum of sizes of positive and negative numbers
    // is less than the size of A, then there must be a 0
    if (heappos.size() + heapneg.size() < A.size())
    {
        zeroflag = true;
    }

    make_heap(heappos.begin(), heappos.end());
    make_heap(heapneg.begin(), heapneg.end());
    make_heap(heapposflip.begin(), heapposflip.end());
    make_heap(heapnegflip.begin(), heapnegflip.end());

    // cout << "heappos: " << heappos.size() << endl;
    // cout << "heapneg: " << heapneg.size() << endl;

    // int heappossize = heappos.size();
    // int heapnegsize = heapneg.size();

    // for (int num : heappos)
    //     cout << num << " ";
    // cout << endl;
    // for (int num : heapneg)
    //     cout << num << " ";
    // cout << endl;

    // for (int i = 0; i < heappossize; ++i)
    // {
    //     pop_heap(heappos.begin(), heappos.end());
    //     int popnum = heappos.back();
    //     cout << popnum << " ";
    //     heappos.pop_back();
    // }
    // cout << endl;
    // for (int i = 0; i < heapnegsize; ++i)
    // {
    //     pop_heap(heapneg.begin(), heapneg.end());
    //     int popnum = heapneg.back();
    //     cout << popnum << " ";
    //     heapneg.pop_back();
    // }
    // cout << endl;

    // positive number, so need largest magnitude
    // (a) 1 pos, 2 neg
    // (a1) pop 1 from heappos, (a2) pop 2 from heapnegflip
    // (b) all 3 pos
    // (b1) pop 3 from heappos

	// find negative numbers only if no positive numbers, and no zeros

    // negative number, so need smallest magnitude
    // (c) 2 pos, 1 neg:
    // (c1) pop 2 from heapposflip, (c2) pop 1 from heapneg
    // (d) all 3 neg
    // (d1) pop 3 from heapneg

    vector<int> answers;

    if (heappos.size() > 0)
    {
        // cout << "size: " << heappos.size() << endl;
        pop_heap(heappos.begin(), heappos.end());
        int factor = heappos.back();
        heappos.pop_back();
        // cout << "size: " << heappos.size() << endl;
        // cout << "factor: " << factor << endl;

        // (a) 1 pos, 2 neg
        // (a1) pop 1 from heappos, (a2) pop 2 from heapnegflip
        int answer = factor;
        if (heapnegflip.size() >= 2)
        {
            for (int i = 0; i < 2; ++i)
            {        
                pop_heap(heapnegflip.begin(), heapnegflip.end());
                // no need to flip negative sign, since two negative numbers
                // being multipled cancel out negative signs 
                answer *= heapnegflip.back();
                heapnegflip.pop_back();
            }
            answers.push_back(answer);
        }

        // (b) all 3 pos
        // (b1) pop 3 from heappos
        // first of 3 popped already
        answer = factor;
        if (heappos.size() >= 2)
        {
            for (int i = 0; i < 2; ++i)
            {        
                pop_heap(heappos.begin(), heappos.end());
                answer *= heappos.back();
                heappos.pop_back();
            }
            answers.push_back(answer);
        }

        // if there is a positive answer, then return largest
        if (answers.size() > 0)
        {
            make_heap(answers.begin(), answers.end());
            pop_heap(answers.begin(), answers.end());
            return answers.back();
        }
    }

    // if there are no positive answers, then 0 is the best answer
    if (zeroflag)
    {
        return 0;
    }

    // no positive answer and no 0 answer, so find least negative answer
    // cout << "size: " << heapneg.size() << endl;
    pop_heap(heapneg.begin(), heapneg.end());
    int factor = heapneg.back();
    heapneg.pop_back();

    // (c) 2 pos, 1 neg:
    // (c1) pop 2 from heapposflip, (c2) pop 1 from heapneg
    int answer = factor;
    if (heapposflip.size() >= 2)
    {
        for (int i = 0; i < 2; ++i)
        {        
            pop_heap(heapposflip.begin(), heapposflip.end());
            answer *= -heapposflip.back();
            heapposflip.pop_back();
        }
        answers.push_back(answer);
    }

    // (d) all 3 neg
    // (d1) pop 3 from heapneg
    // first of 3 popped already
    answer = factor;
    if (heapneg.size() >= 2)
    {
        for (int i = 0; i < 2; ++i)
        {        
            pop_heap(heapneg.begin(), heapneg.end());
            answer *= heapneg.back();
            heapneg.pop_back();
        }
        answers.push_back(answer);
    }

    make_heap(answers.begin(), answers.end());
    pop_heap(answers.begin(), answers.end());
    return answers.back();
}