// Longest increasing subsequence algorithm
// Implemented via both recursive and iterative DP here
#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007

typedef long long ll;

int lis_dp_rec(vector<int>& P, vector<int>& DP, vector<int>& A, int index) {
	if (DP[index] != -1) return DP[index];
	// cout << "Solving rec for A[" << index << "] = " << A[index] << endl;
	int max_subprob_sol = 0;
	int max_subprob_sol_idx = -1;
	for (int i=index-1; i>=0; i--) {
		if (A[i] < A[index]) {
			int subproblem_sol = lis_dp_rec(P,DP,A,i);
			if (subproblem_sol > max_subprob_sol) {
				max_subprob_sol = subproblem_sol;
				max_subprob_sol_idx = i;
			}
		}
	}
	DP[index] = max_subprob_sol + 1;
	P[index] = max_subprob_sol_idx;
	return max_subprob_sol + 1;
}

vector<int> lis_dp_iter(vector<int>& A) {

	int n = A.size();
	vector<int> DP(n, -1);
	vector<int> P(n, -1);
	for (int i=0; i<n; i++) {
		int lis_i = 0;
		int lis_i_idx = -1;
		for (int j=i-1; j>=0; j--) {
			if (A[j] < A[i] && DP[j] > lis_i) {
				lis_i = DP[j];
				lis_i_idx = j;
			}
		}
		P[i] = lis_i_idx;
		DP[i] = lis_i + 1;
	}

	int len_lis = *max_element(DP.begin(), DP.end());
	vector<int> s(len_lis);
	int idx = max_element(DP.begin(), DP.end()) - DP.begin();
	for (int i=len_lis-1; i>=0; i--) {
		s[i] = A[idx];
		idx = P[idx];
	}

	return s;
}

int main() {
	
	int t;
	cin >> t;
	while (t-- > 0) {
		int n;
		cin >> n;
		vector<int> A(n);
		for (int i=0; i<n; i++) cin >> A[i];
		vector<int> lis = lis_dp_iter(A);
		for (auto i : lis) {
			cout << i << " ";
		}
		cout << endl;
	}

	return 0;
}
