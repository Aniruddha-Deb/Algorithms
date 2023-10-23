#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007

typedef long long ll;

int main() {

    int n;
    cin >> n;
    vector<int> A(n+1,0);

    for (int i=1; i<=n; i++) cin >> A[i];

    vector<vector<int>> DP(n+1,vector<int>(n+1,0));

    /*
    
    Player 1 and 2 play a game, where they can remove a coin from either end of a chain
    of coins until the chain is empty. Each coin has a value associated with it. 
    If both Player 1 and 2 play optimally, what is the maximum score Player 1 can get?

    Note that this is a zero-sum game, i.e. anything player 1 won't pick up will 
    be picked up by player 2, hence we can model it as a minmax problem for 
    player 1. Also, note that Player 1 will move when the parity of the leftover
    coins is the same as the initial parity. This allows for easier memoization, 
    where we don't have to mantain two arrays

    The recursion is then given by
    P(i,j) = max(P(i,j-1)+A[j], P(i+1,j)+A[i]) if (j-i+1)%2 == n%2
             min(P(i,j-1),P(i+1,j)) if (j-i+1)%2 != n%2
    And the base case is
    P(i,i) = A[i] if n%2 == 1   = A[i]*(n%2)
             0 if n%2 == 0
    */

    int p = n%2;

    for (int j=1; j<=n; j++) {
        DP[j][j] = A[j]*p;
        for (int i=j-1; i>=1; i--) { // note the loop order here; to mantain the order
                                     // in which we solve subproblems
            if ((j-i+1)%2 == p) {
                DP[i][j] = max(DP[i][j-1]+A[j], DP[i+1][j]+A[i]);
            }
            else {
                DP[i][j] = min(DP[i][j-1], DP[i+1][j]);
            }
        }
    }

    cout << DP[1][n] << endl;

    return 0;
}
