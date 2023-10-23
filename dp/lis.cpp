#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007

typedef long long ll;

int main() {

    int n;
    cin >> n;
    vector<int> A(n+1,0);
    for (int i=1; i<=n; i++) cin >> A[i];

    vector<int> DP(n+1,0);
    vector<int> LIS(n+1,0);
    for (int i=1; i<=n; i++) {
        int dp_max = INT_MIN;
        int dpm_idx = 0;
        for (int j=0; j<i; j++) {
            if (A[j] < A[i] && DP[j]+1 > dp_max) {
                dp_max = DP[j]+1;
                dpm_idx = j;
            }
        }
        DP[i] = dp_max;
        LIS[i] = dpm_idx;
    }

    int max_lis = n;
    for (int i=n-1; i>0; i--) {
        if (DP[i] > DP[max_lis]) max_lis = i;
    }

    stack<int> lis;
    for (int i=max_lis; i>0; ) {
        lis.push(A[i]);
        i = LIS[i];
    }

    while (!lis.empty()) {
        cout << lis.top() << " ";
        lis.pop();
    }
    cout << endl;

    return 0;
}
