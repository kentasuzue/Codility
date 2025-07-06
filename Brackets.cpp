/*
Task description
A string S consisting of N characters is considered to be properly nested if any of the following conditions is true:

S is empty;
S has the form "(U)" or "[U]" or "{U}" where U is a properly nested string;
S has the form "VW" where V and W are properly nested strings.
For example, the string "{[()()]}" is properly nested but "([)()]" is not.

Write a function:

int solution(string &S);

that, given a string S consisting of N characters, returns 1 if S is properly nested and 0 otherwise.

For example, given S = "{[()()]}", the function should return 1 and given S = "([)()]", the function should return 0, as explained above.

Write an efficient algorithm for the following assumptions:

N is an integer within the range [0..200,000];
string S is made only of the following characters: '(', '{', '[', ']', '}' and/or ')'.
*/

// you can use includes, for example:
// #include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;
#include <iostream>
#include <stack>
#include <unordered_map>
#include <unordered_set>

int solution(string &S) {
    // Implement your solution here
    unordered_map<char, char> map_open_close;
    map_open_close['('] = ')';
    map_open_close['{'] = '}';
    map_open_close['['] = ']';

    unordered_set<char> set_open = {'(', '{', '['};

    // cout << map_open_close['('] << endl;
    // cout << map_open_close['{'] << endl;
    // cout << map_open_close['['] << endl;

    stack<char> nest;

    for (char c : S)
    {
		// if c is opening bracket then push
        if (set_open.find(c) != set_open.end())
        {
            nest.push(c);
        }
		// c is closing bracket
        else 
        {
			// empty stack means no matching opening bracket exists 
            if (nest.size() == 0)
                return 0;
			// mismatching opening bracket in stack 
            if (map_open_close[nest.top()] != c)
                return 0;
			// pop matching opening bracket
            nest.pop();
        }
    }
	// leftover opening bracket(s)
    if (nest.size() > 0)
        return 0;
    return 1;
}