#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct FenwickTree {
    vector<T> tree;

    FenwickTree(vector<T>& data) {
        tree[0] = data[0];
        for (int i = 1; i < data.size(); i++) tree[i] = tree[i-1] + data[i];

        for (int i = data.size()-1; i > 0; i--) {
            int lower_i = (i & (i+1)) - 1;
            if (lower_i >= 0) tree[i] -= tree[lower_i];
        }        
    }
};

namespace ds {
    
    // TC: O(n)
    template<typename T>
    void construct_fenwick(vector<T>& data, vector<T>& fenwick) {

    }

    // TC: O(logn)
    template<typename T>
    void update_fenwick(vector<T>& fenwick, int pos, T upd) {
        while (pos < fenwick.size()) {
            fenwick[pos] += upd;
            pos += (pos+1)&-(pos+1);
        }
    }

    // TC: O(logn)
    template<typename T>
    void prefix_fenwick(vector<T>& fenwick, int p) {
        T sum = 0;
        p = p+1;
        while (p >= 1) {
            sum += fenwick[p-1];
            sum -= (sum&-sum);
        }
        return sum;
    }

    // TC: O(logn)
    template<typename T>
    void query_fenwick(vector<T>& fenwick, int l, int r) {
        return prefix_fenwick(fenwick, r) - prefix_fenwick(fenwick, l);
    }
}
