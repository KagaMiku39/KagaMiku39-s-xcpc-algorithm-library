#include <bits/stdc++.h>

using namespace std;

template<typename T>
bool cmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

struct Trie {
    static constexpr int maxsz = 3.1e6 + 1;
    
    int idx{}; 
    
    struct Node {
        array<int, 2> adj;
    };
    vector<Node> tr; 
    
    Trie() {
        tr.emplace_back(); 
    }

    // Trie() : tr(maxsz) {}
    
    void insert(int val) {
        int cur = 0;
        for (int i = 31; ~i; i --) {
            bool j = val >> i & 1;
            if (!tr[cur].adj[j]) {
                tr[cur].adj[j] = ++ idx;
                tr.emplace_back();
            }
            cur = tr[cur].adj[j];
        }
    }

    int query(int val) {
        int res = 0, cur = 0;
        for (int i = 31; ~i; i --) {
            bool j = val >> i & 1;
            if (tr[cur].adj[!j]) {
                res |= 1 << i;
                cur = tr[cur].adj[!j];
            } else {
                cur = tr[cur].adj[j];
            }
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    
    vector<int> a(n + 1);
    Trie tr;
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
        tr.insert(a[i]);
    }
    
    int ans = 0;
    for (int i = 1; i <= n; i ++) {
        cmax(ans, tr.query(a[i]));
    }

    cout << ans << '\n';

    return 0;
}