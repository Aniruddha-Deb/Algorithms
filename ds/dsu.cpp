#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007

typedef long long ll;

namespace ds {

// taken from cp-algorithms.com
class dsu {

    public:

    unordered_map<int,int> parent;
    unordered_map<int,int> size;

    int find_set(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = find_set(parent[v]);
    }

    void make_set(int v) {
        parent[v] = v;
        size[v] = 1;
    }

    void union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (size[a] < size[b])
                swap(a, b);
            parent[b] = a;
            size[a] += size[b];
        }
    }
};

};

int main() {

    ds::dsu dsu;

    dsu.make_set(1);
    dsu.make_set(2);
    dsu.make_set(3);
    dsu.make_set(4);

    dsu.union_sets(1,2);
    dsu.union_sets(1,3);

    cout << dsu.find_set(2) << " " << dsu.find_set(3) << "\n";
    cout << dsu.find_set(1) << " " << dsu.find_set(4) << "\n";

    return 0;
}
