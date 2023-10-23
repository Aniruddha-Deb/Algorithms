#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

#define MOD 1000000007
#define MOD2 998244353
#define rep(i, a, b) for (auto i = (a); i < (b); i++)
#define per(i, a, b) for (auto i = (a); i >= (b); i--)

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
 
typedef pair<int, int> interval;
 
// PBDS for an interval tree 
// should be max_high and min_low, and has_nonoverlap_pair should become has_overlap_pair
template <class Node_CItr,
          class Node_Itr,
          class Cmp_Fn, class _Alloc>
struct interval_node_update_policy {
 
    typedef pair<int,int> metadata_type;
 
    bool has_nonoverlap_pair_rec(Node_CItr it) {
        if (it == node_end()) return false;

        // max_low > min_high
        if (it.get_metadata().first > it.get_metadata().second) {
            // cout << it.get_metadata().first << " " << it.get_metadata().second << "\n";
            return true;
        }

        bool has_left_overlap = has_nonoverlap_pair_rec(it.get_l_child());
        bool has_right_overlap = has_nonoverlap_pair_rec(it.get_r_child());

        return has_left_overlap || has_right_overlap;
    }

    bool has_nonoverlap_pair() {
        return has_nonoverlap_pair_rec(node_begin());
    }
 
    void operator()(Node_Itr it, Node_CItr end_it) {

        int min_high = (*it)->second;
        int max_low  = (*it)->first;
 
        if (it.get_l_child() != end_it) {
            min_high = min(min_high, it.get_l_child().get_metadata().second);
        }
        if (it.get_r_child() != end_it) {
            max_low  = max(max_low, it.get_r_child().get_metadata().first);
        }
 
        const_cast<pair<int,int>&>(it.get_metadata()) = pair<int,int>(max_low, min_high);
    }
 
    virtual Node_CItr node_begin() const = 0;
    virtual Node_CItr node_end() const = 0;
    virtual ~interval_node_update_policy() {}
};

typedef tree<interval,
             null_type,
             less_equal<interval>,
             rb_tree_tag,
             interval_node_update_policy>
    intervalTree;
 
void solve() {

    int q;
    cin >> q;

    intervalTree it;

    map<ll, bool> causes_overlap;

    while (q-- > 0) {

        char c;
        int l, r;
        cin >> c >> l >> r;

        interval p(l,r);

        if (c == '+') it.insert(p);
        else it.erase(it.upper_bound(p));

        // for (auto p : it) {
        //    cout << "(" << p.first << "," << p.second << ") ";
        //}
        //cout << "\n";

        if (it.has_nonoverlap_pair()) cout << "YES\n";
        else cout << "NO\n";
    }

}

int main(int argc, char** argv) {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t = 1;
    // cin >> t;
    while (t-- > 0) {
        solve();
    }
    return 0;
}

