#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007

typedef long long ll;

namespace ds {

template<typename T, typename M>
struct rbtree_node {
    T data;
    M metadata;
    rbtree_node<T,M> *p;
    rbtree_node<T,M> *left, *right;
    bool red;

    rbtree_node(T _data): 
        data{_data}, 
        metadata{}, 
        p{nullptr}, 
        left{nullptr}, 
        right{nullptr},
        red{false}
    {}

    rbtree_node():
        data{},
        metadata{},
        p{nullptr},
        left{nullptr},
        right{nullptr},
        red{false}
    {}
};

template<typename T, typename M, typename Compare = std::less_equal<T>>
class rbtree {

    protected:
    void left_rotate(rbtree_node<T,M>* x) {
        auto y = x->right;
        x->right = y->left;
        if (y->left != nil) {
            y->left->p = x;
        }
        y->p = x->p;
        if (x->p == nil) {
            root = y;
        }
        else if (x == x->p->left) {
            x->p->left = y;
        }
        else {
            x->p->right = y;
        }
        y->left = x;
        x->p = y;
    }

    void right_rotate(rbtree_node<T,M>* x) {
        auto y = x->left;
        x->left = y->right;
        if (y->right != nil) {
            y->right->p = x;
        }
        y->p = x->p;
        if (x->p == nil) {
            root = y;
        }
        else if (x == x->p->right) {
            x->p->right = y;
        }
        else {
            x->p->left = y;
        }
        y->right = x;
        x->p = y;
    }

    void insert_fixup(rbtree_node<T,M>* z) {
        while (z->p->red) {
            if (z->p == z->p->p->left) {
                auto y = z->p->p->right;
                if (y->red) {
                    z->p->red = false;
                    y->red = false;
                    z->p->p->red = true;
                    z = z->p->p;
                }
                else {
                    if (z == z->p->right) {
                        z = z->p;
                        left_rotate(z);
                    }
                    z->p->red = false;
                    z->p->p->red = true;
                    right_rotate(z->p->p);
                }
            }
            else {
                auto y = z->p->p->left;
                if (y->red) {
                    z->p->red = false;
                    y->red = false;
                    z->p->p->red = true;
                    z = z->p->p;
                }
                else {
                    if (z == z->p->left) {
                        z = z->p;
                        right_rotate(z);
                    }
                    z->p->red = false;
                    z->p->p->red = true;
                    left_rotate(z->p->p);
                }
            }
        }
        root->red = false;
    }

    void delete_fixup(rbtree_node<T,M>* x) {

        while (x != root && !x->red) {
            if (x == x->p->left) {
                auto w = x->p->right;
                if (w->red) {
                    w->red = false;
                    x->p->red = true;
                    left_rotate(x->p);
                    w = x->p->right;
                }
                if (!w->left->red && !w->right->red) {
                    w->red = true;
                    x = x->p;
                }
                else {
                    if (!w->right->red) {
                        w->left->red = false;
                        w->red = true;
                        right_rotate(w);
                        w = x->p->right;
                    }
                    w->red = x->p->red;
                    x->p->red = false;
                    w->right->red = false;
                    left_rotate(x->p);
                    x = root;
                }
            }
            else {
                auto w = x->p->left;
                if (w->red) {
                    w->red = false;
                    x->p->red = true;
                    right_rotate(x->p);
                    w = x->p->left;
                }
                if (!w->right->red && !w->left->red) {
                    w->red = true;
                    x = x->p;
                }
                else {
                    if (!w->left->red) {
                        w->right->red = false;
                        w->red = true;
                        left_rotate(w);
                        w = x->p->left;
                    }
                    w->red = x->p->red;
                    x->p->red = false;
                    w->left->red = false;
                    right_rotate(x->p);
                    x = root;
                }
            }
        }
    }

    void transplant(rbtree_node<T,M>* u, rbtree_node<T,M>* v) {
        if (u->p == nil) {
            root = v;
        }
        else if (u == u->p->left) {
            u->p->left = v;
        }
        else {
            u->p->right = v;
        }
        v->p = u->p;
    }

    rbtree_node<T,M>* tree_minimum(rbtree_node<T,M>* z) {
        while (z->left != nil) z = z->left;
        return z;
    }

    void print_rec(rbtree_node<T,M>* n, string prefix) {


        string p;
        if (n != root) p = prefix.substr(0, prefix.length()-2) + "`-";
        if (n == nil) {
            cout << p << "n\n";
            return;
        }
        else if (n->red) {
            cout << p << "[" << n->data << "]\n";
        }
        else {
            cout << p << n->data << "\n";
        }
        if (n->right == nil && n->left == nil) return;
        print_rec(n->right, prefix + "| ");
        print_rec(n->left,  prefix + "  ");

    }

    public:
    rbtree_node<T,M>* root;
    rbtree_node<T,M>* nil;
    Compare cmp;

    void insert(T data) {
        rbtree_node<T,M> *z = new rbtree_node<T,M>(data);
        auto x = root;
        auto y = nil;
        while (x != nil) {
            y = x;
            if (cmp(z->data, x->data)) x = x->left;
            else x = x->right;
        }
        z->p = y;
        if (y == nil) {
            root = z;
        }
        else if (cmp(z->data, y->data)) {
            y->left = z;
        }
        else {
            y->right = z;
        }

        z->left = nil;
        z->right = nil;
        z->red = true;

        insert_fixup(z);
    }

    rbtree_node<T,M>* find(T data) {

        auto z = root;
        while (z != nil && !(cmp(z->data,data) && cmp(data,z->data))) {
            if (cmp(data, z->data)) {
                z = z->left;
            }
            else {
                z = z->right;
            }
        }

        return z;
    }

    void erase(T data) {
        auto z = find(data);
        auto y = z;
        bool y_originally_red = y->red;
        auto x = z->left;

        if (z->left == nil) {
            x = z->right;
            transplant(z, z->right);
        }
        else if (z->right == nil) {
            x = z->left;
            transplant(z, z->left);
        }
        else {
            y = tree_minimum(z->right);
            y_originally_red = y->red;
            x = y->right;
            if (y != z->right) {
                transplant(y, y->right);
                y->right = z->right;
                y->right->p = y;
            }
            else {
                x->p = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->p = y;
            y->red = z->red;
        }

        if (!y_originally_red) {
            delete_fixup(x);
        }
    }

    void print() {
        print_rec(root, "");
    }

    rbtree(): cmp{std::less_equal<T>()} {
        nil = new rbtree_node<T,M>();
        nil->p = nil;
        nil->left = nil;
        nil->right = nil;
        nil->red = false;

        root = nil;
    }
    rbtree(Compare _cmp): cmp{_cmp} {
        nil = new rbtree_node<T,M>();
        nil->p = nil;
        nil->left = nil;
        nil->right = nil;
        nil->red = false;

        root = nil;
    }
};

};

int main() {

    ds::rbtree<int,int> tree;

    tree.insert(5);
    tree.insert(4);
    tree.insert(2);
    tree.insert(3);
    tree.insert(6);
    tree.insert(1);
    tree.insert(7);

    tree.print();

    tree.erase(4);
    tree.print();

    tree.insert(4);
    tree.insert(4);
    tree.insert(4);
    tree.insert(4);
    tree.insert(4);

    tree.print();

    tree.erase(4);
    tree.erase(4);
    tree.print();


    return 0;
}
