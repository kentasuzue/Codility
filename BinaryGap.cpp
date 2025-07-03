/*
Task description
A binary gap within a positive integer N is any maximal sequence of consecutive zeros that is surrounded by ones at both ends in the binary representation of N.

For example, number 9 has binary representation 1001 and contains a binary gap of length 2. The number 529 has binary representation 1000010001 and contains two binary gaps: one of length 4 and one of length 3. The number 20 has binary representation 10100 and contains one binary gap of length 1. The number 15 has binary representation 1111 and has no binary gaps. The number 32 has binary representation 100000 and has no binary gaps.

Write a function:

int solution(int N);

that, given a positive integer N, returns the length of its longest binary gap. The function should return 0 if N doesn't contain a binary gap.

For example, given N = 1041 the function should return 5, because N has binary representation 10000010001 and so its longest binary gap is of length 5. Given N = 32 the function should return 0, because N has binary representation '100000' and thus no binary gaps.

Write an efficient algorithm for the following assumptions:

N is an integer within the range [1..2,147,483,647].
*/


// you can use includes, for example:
// #include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

#include <iostream>
#include <string>
#include <bitset>

using namespace std;

int solution(int N) {
    // Implement your solution here
    // 32 bit binary representation of N
    bitset<32> bitinteger(N);
    string bitstring = bitinteger.to_string();
    size_t strbegin = bitstring.find("1");
    size_t strend = bitstring.find_last_of("1");
    // if first and last "1" are the same, there's only a single "1"
    if (strbegin == strend) return 0;
    // substring beginning with first "1" and ending with last "1" 
    // necessary to terminate with "1" to omit trailing "0"'s
    string noleadbitstring = bitstring.substr(strbegin, strend - strbegin + 1);

    int zerocount = 0;
    int maxzerocount = 0;
    for (string::iterator it = noleadbitstring.begin(); it != noleadbitstring.end();
    ++it)
    {
        if (*it == '1')
        {
            zerocount = 0;
        }
        // *it == '0'
        else
        {
            zerocount++;
            if (zerocount > maxzerocount)
                maxzerocount = zerocount;
        }
    }
    // cout << "maxzerocount: " << maxzerocount << endl;
    // cout << "N" << N << endl;
    // cout << noleadbitstring << endl;
    // cout << noleadbitstring.size() << endl;
    return maxzerocount;
}
