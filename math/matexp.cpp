#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007
#define MOD2 998244353
#define rep(i, a, b) for (auto i = (a); i < (b); i++)

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;

#define K 10

using Matrix = array<array<ll, K>, K>;

Matrix ID   = {{{1,0,0,0,0,0,0,0,0,0},
                {0,1,0,0,0,0,0,0,0,0},
                {0,0,1,0,0,0,0,0,0,0},
                {0,0,0,1,0,0,0,0,0,0},
                {0,0,0,0,1,0,0,0,0,0},
                {0,0,0,0,0,1,0,0,0,0},
                {0,0,0,0,0,0,1,0,0,0},
                {0,0,0,0,0,0,0,1,0,0},
                {0,0,0,0,0,0,0,0,1,0},
                {0,0,0,0,0,0,0,0,0,1}}};

Matrix mul(Matrix a, Matrix b) {
    Matrix res{};
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < K; j++) {
            for (int k = 0; k < K; k++) {
                res[i][j] += a[i][k] * b[k][j];
                res[i][j] %= MOD;
            }
        }
    }

    return res;
}

Matrix add(Matrix a, Matrix b) {
    Matrix res{};
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < K; j++) {
            res[i][j] += a[i][j] + b[i][j];
            res[i][j] %= MOD;
        }
    }

    return res;
}

vector<Matrix> matpows(18);

void solve() {

    int n, m;
    cin >> n >> m;

    vector<ll> A(10, 0);
    while (n > 0) {
        int d = n % 10;
        A[d] += 1;
        n /= 10;
    }

    int k = 0;
    while (m > 0) {
        if (m & 1) {
            vector<ll> B(10, 0);
            for (int i=0; i<K; i++) {
                for (int j=0; j<K; j++) {
                    // cout << T[i][j] << " ";
                    B[i] += matpows[k][i][j] * A[j];
                    B[i] %= MOD;
                }
                // cout << "\n";
            }
            for (int i=0; i<K; i++) A[i] = B[i];
        }
        m /= 2;
        k++;
    }

    ll sum = 0;
    for (int i=0; i<10; i++) {
        sum = (sum + A[i]) % MOD;
    }

    cout << sum << endl;

}

void precompute() {

    Matrix base = {{{0,0,0,0,0,0,0,0,0,1},
                    {1,0,0,0,0,0,0,0,0,1},
                    {0,1,0,0,0,0,0,0,0,0},
                    {0,0,1,0,0,0,0,0,0,0},
                    {0,0,0,1,0,0,0,0,0,0},
                    {0,0,0,0,1,0,0,0,0,0},
                    {0,0,0,0,0,1,0,0,0,0},
                    {0,0,0,0,0,0,1,0,0,0},
                    {0,0,0,0,0,0,0,1,0,0},
                    {0,0,0,0,0,0,0,0,1,0}}};
    
    matpows[0] = base;

    rep(i, 1, 18) {
        matpows[i] = mul(matpows[i-1], matpows[i-1]);
    }
}

int main(int argc, char** argv) {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    precompute();

    int t = 1;
    cin >> t;
    while (t-- > 0) {
        solve();
    }
    return 0;
}

