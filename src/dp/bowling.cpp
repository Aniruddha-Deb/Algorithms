#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007

typedef long long ll;

int main() {
    
    int n;
    cin >> n;

    vector<int> V(n+1);

    for (int i=1; i<=n; i++) cin >> V[i];

    vector<int> DP(n+1,0);
    for (int i=1; i<=n; i++) {
        if (i > 1) {
            DP[i] = max(DP[i-1],max(DP[i-1]+V[i],DP[i-2]+V[i]*V[i-1]));
        }
        else {
            DP[i] = max(0,V[i]);
        }
    }

    cout << DP[n] << endl;

    return 0;
}
