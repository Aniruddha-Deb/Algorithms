#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007

typedef long long ll;

int main() {
    
    string u, v;
    cin >> u >> v;
    int lu = u.size(), lv = v.size();

    vector<vector<int>> DP(lu+1, vector<int>(lv+1,0));
    vector<vector<int>> LCS(lu+1, vector<int>(lv+1,0));

    for (int i=1; i<=lu; i++) {
        for (int j=1; j<=lv; j++) {
            if (u[i-1] == v[j-1]) {
                DP[i][j] = 1 + DP[i-1][j-1];
                LCS[i][j] = 3;
            }
            else {
                DP[i][j] = max(DP[i-1][j], DP[i][j-1]);
                if (DP[i][j] == DP[i-1][j]) LCS[i][j] = 2;
                else LCS[i][j] = 1;
            }
        }
    }

    int i=lu,j=lv;
    string lcs = "";
    while (i>0 && j>0) {
        if (LCS[i][j] == 3) {
            lcs = u[i-1] + lcs;
            i--; j--;
        }
        else if (LCS[i][j] == 2) {
            i--;
        }
        else {
            j--;
        }
    }

    cout << lcs << endl;
    return 0;
}
