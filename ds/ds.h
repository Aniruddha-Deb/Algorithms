#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct FenwickTree {
    vector<T> tree;

    FenwickTree(vector<T>& data) {
        fenwick[0] = data[0];
        for (int i = 1; i < data.size(); i++) fenwick[i] = fenwick[i-1] + a[i];

        for (int i = a.size()-1; i > 0; i--) {
            int lower_i = (i & (i+1)) - 1;
            if (lower_i >= 0) fenwick[i] -= fenwick[lower_i];
        }        
    }
}

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
        return prefix_fenwick(r) - prefix_fenwick(l);
    }
}
