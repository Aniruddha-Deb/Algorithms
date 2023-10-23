#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void dfs_rec(vector<vector<int>>& G, int root, vector<bool>& visited) {
	visited[root] = true;
	cout << root << " ";
	for (int i : G[root]) {
		if (!visited[i]) dfs_rec(G,i,visited);
	}
}

// iterative versions of BFS and DFS only differ in the queue
// in DFS, the queue is replaced with a stack
// the recursive definition of DFS is much smoother, though.
void dfs(vector<vector<int>>& G, int root) {
	int n = G.size();
	stack<int> s;
	vector<bool> visited(n, false);
	
	s.push(root);
	visited[root] = true;
	while (!s.empty()) {
		int v = s.top();
		cout << v << " ";
		s.pop();
		for (int u : G[v]) {
			if (!visited[u]) {
				visited[u] = true;
				s.push(u);
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

	dfs(G,1);
	
	//vector<bool> v(n+1,false);
	//dfs_rec(G,1,v);

	return 0;
}
