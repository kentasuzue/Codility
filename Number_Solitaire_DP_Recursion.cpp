/*
Task description
A game for one player is played on a board consisting of N consecutive squares, numbered from 0 to N − 1. There is a number written on each square. A non-empty array A of N integers contains the numbers written on the squares. Moreover, some squares can be marked during the game.

At the beginning of the game, there is a pebble on square number 0 and this is the only square on the board which is marked. The goal of the game is to move the pebble to square number N − 1.

During each turn we throw a six-sided die, with numbers from 1 to 6 on its faces, and consider the number K, which shows on the upper face after the die comes to rest. Then we move the pebble standing on square number I to square number I + K, providing that square number I + K exists. If square number I + K does not exist, we throw the die again until we obtain a valid move. Finally, we mark square number I + K.

After the game finishes (when the pebble is standing on square number N − 1), we calculate the result. The result of the game is the sum of the numbers written on all marked squares.

For example, given the following array:

    A[0] = 1
    A[1] = -2
    A[2] = 0
    A[3] = 9
    A[4] = -1
    A[5] = -2
one possible game could be as follows:

the pebble is on square number 0, which is marked;
we throw 3; the pebble moves from square number 0 to square number 3; we mark square number 3;
we throw 5; the pebble does not move, since there is no square number 8 on the board;
we throw 2; the pebble moves to square number 5; we mark this square and the game ends.
The marked squares are 0, 3 and 5, so the result of the game is 1 + 9 + (−2) = 8. This is the maximal possible result that can be achieved on this board.

Write a function:

int solution(vector<int> &A);

that, given a non-empty array A of N integers, returns the maximal result that can be achieved on the board represented by array A.

For example, given the array

    A[0] = 1
    A[1] = -2
    A[2] = 0
    A[3] = 9
    A[4] = -1
    A[5] = -2
the function should return 8, as explained above.

Write an efficient algorithm for the following assumptions:

N is an integer within the range [2..100,000];
each element of array A is an integer within the range [−10,000..10,000].
*/

// you can use includes, for example:
// #include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

#include <iostream>
#include <vector>
#include <algorithm>

// worst case answer is about -10,000 * 100,000 / 6
// so a vector element with LOW_INT was never accessed after initialization
#define LOW_INT -200'000'000

using namespace std;

vector<int> dp_answer;

// dp(i) = A[i] + dp(j)

int dp(int square, int N, vector<int> &A)
{
    if (dp_answer[square] != LOW_INT)
    {
        return dp_answer[square];
    }

    // die roll of up to 6, and N - 1 is maximum vector index 
    int upper_bound = min(N - 1, square + 6);

    // at least the vector index i + 1 is updated
    // the number of updated indexes is up to 6, with maximum index of  N - 1
    for (int j = square + 1; j <= upper_bound; ++j)
    {
        // cached answer must be larger to be updated
        // cached answer was initialized with LOW_INT
        dp_answer[square] = max(dp_answer[square], A[square] + dp(j, N, A) );
    }
    return dp_answer[square];
}

int solution(vector<int> &A) {
    // Implement your solution here
    int N = A.size();

    dp_answer.resize(A.size());

    for (int i = 0; i < N; ++i)
    {
        // worst case answer is about -10,000 * 100,000 / 6
        dp_answer[i] = LOW_INT;
    }

    // cout << dp_answer.size() << endl;
    // cout << dp_answer[A.size() - 1] << endl;

    dp_answer[N-1] = A[N-1];

    // beginning index is 0 which is smallest vector index
    // ending index is N-2 since from index N-2 at least index N-1 is updated
    // ending index is not N-1 since no indexes >= N are updated
    for (int i = 0; i <= N - 2; ++i)
    {
        dp(i, N, A);
    }

	// answer is stored at 0 index, the starting index of the game
    return dp_answer[0];
}