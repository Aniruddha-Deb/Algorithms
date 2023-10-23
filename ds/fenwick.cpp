#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007

typedef long long ll;

namespace ds {
    
template<typename T>
class fenwick_tree {

    vector<T> tree;

    fenwick_tree(vector<T>& data) {
        tree[0] = data[0];
        for (int i = 1; i < data.size(); i++) tree[i] = tree[i-1] + data[i];

        for (int i = data.size()-1; i > 0; i--) {
            int lower_i = (i & (i+1)) - 1;
            if (lower_i >= 0) tree[i] -= tree[lower_i];
        }        
    }
   
    // TC: O(logn)
    void update(int pos, T upd) {
        while (pos < tree.size()) {
            tree[pos] += upd;
            pos += (pos+1)&-(pos+1);
        }
    }

    // TC: O(logn)
    void prefix_fenwick(int p) {
        T sum = 0;
        p = p+1;
        while (p >= 1) {
            sum += tree[p-1];
            sum -= (sum&-sum);
        }
        return sum;
    }

    // TC: O(logn)
    void query_fenwick(int l, int r) {
        return prefix_fenwick(tree, r) - prefix_fenwick(tree, l);
    }
};

}

int main() {

    // this answers sum queries using binary indexing
    // int n;
    // cin >> n;
    // vector<int> V(n);
    // for (int i=0; i<n; i++) cin >> V[i];

    // vector<int> F(n);
    // construct_fenwick_tree(V,F);

    // int q;
    // cin >> 

    ds::test_func(5,6);


    return 0;
}
