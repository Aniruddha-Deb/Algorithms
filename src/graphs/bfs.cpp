#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void bfs(vector<vector<int>>& G, int root) {
	int n = G.size();
	queue<int> q;
	vector<bool> visited(n, false);
	
	q.push(root);
	visited[root] = true;
	while (!q.empty()) {
		int v = q.front();
		cout << v << " ";
		q.pop();
		for (int u : G[v]) {
			if (!visited[u]) {
				visited[u] = true;
				q.push(u);
			}
		}
	}
	cout << endl;
}

// testing
int main() {

	int n, e;
	cin >> n >> e;
	vector<vector<int>> G(n+1,vector<int>());
	for (int i=0; i<e; i++) {
		int a,b;
		cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}

	bfs(G,1);

	return 0;
}
