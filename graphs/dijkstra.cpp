#include <bits/stdc++.h>
using namespace std;

#define INF INT_MAX

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

void dijkstra(vector<vector<pi>>& G, int root, vi& D) {
	int n = G.size();
	D.assign(n,INF);
	vector<bool> u(n,false);

	D[root] = 0;
	for (int i=0; i<n; i++) {
		int v = -1;
		// select the untraversed node with the least distance
		for (int j=0; j<n; j++) {
			if (!u[j] && (v==-1||D[j]<D[v])) v = j;
		}

		// all nodes left are not connected to the root node
		if (D[v] == INF) break;

		u[v] = true;
		for (auto edge : G[v]) {
			int to = edge.first;
			int l = edge.second;

			if (D[v] + l < D[to]) {
				D[to] = D[v]+l;
			}
		}
	}
}

// testing
int main() {

	int n, e;
	cin >> n >> e;
	vector<vector<pi>> G(n+1,vector<pi>());
	for (int i=0; i<e; i++) {
		int a,b,l;
		cin >> a >> b >> l;
		G[a].push_back({b,l});
		G[b].push_back({a,l});
	}

	vi D(n+1);
	dijkstra(G,1,D);

	for (int i=1; i<=n; i++) cout << D[i] << " ";
	cout << endl;

	return 0;
}
