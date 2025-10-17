#include <bits/stdc++.h>

using namespace std;

template<typename T>
struct SparseTable {
    int lay;

    vector<vector<T>> st;

    vector<int> bceil;
    
    function<T(T, T)> op;

    SparseTable(int n, const vector<T> &vec, function<T(T, T)> op) : bceil(n + 1), op(op) {
        // lay = bceil(n);
        for (int i = 2; i <= n; i++) {
            bceil[i] = bceil[i / 2] + 1;
        }
        lay = bceil[n];
        st.resize(lay + 1);
        st[0] = vec;
        for (int i = 1, j = 1; i <= lay; i ++, j <<= 1) {
            st[i] = st[i - 1];
            for (int k = 1; k + 2 * j - 1 <= n; k ++) {
                st[i][k] = op(st[i - 1][k], st[i - 1][k + j]);
            }
        }
    }
    
    // int highbit(int x) {
    //     for (const int &i: {1, 2, 4, 8, 16}) {
    //         x |= x >> i;
    //     }
    //     return x >> 1 ^ x;
    // }

    // int bceil(int x) {
    //     int h = highbit(x); 
    //     return bitset<32>((h << (x != h)) - 1ul).count();
    // }

    int query(int lo, int ro) {
        int len = ro - lo + 1;
        // int h = highbit(len);
        // return op(st[bceil(h)][lo], st[bceil(h)][ro - h + 1]);
        int c = bceil[len];
        return op(st[c][lo], st[c][ro - (1 << c) + 1]);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }
    
    SparseTable<int> st(n, a, [&](int a, int b) {
        return max(a, b);
    });

    while (m --) {
        int l, r;
        cin >> l >> r;
        cout << st.query(l, r) << '\n';
    }

    return 0;
}