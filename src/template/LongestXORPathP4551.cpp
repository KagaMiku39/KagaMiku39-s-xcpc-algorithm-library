#include <bits/stdc++.h>

using namespace std;

template<typename T>
bool cmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

struct Trie {
    static constexpr int maxsz = 3.1e6 + 1;

    int idx{}; 
    
    struct Node{
        array<int, 2> adj;
    };
    vector<Node> tr; 
    
    // Trie() {
    //     tr.emplace_back(); 
    // }

    Trie() : tr(maxsz) {}
    
    void insert(int val) {
        int cur = 0;
        for (int i = 30; ~i; i --) {
            bool j = val >> i & 1;
            if (!tr[cur].adj[j]) {
                tr[cur].adj[j] = ++ idx;
                // tr.emplace_back();
            }
            cur = tr[cur].adj[j];
        }
    }

    int query(int val) {
        if (!idx) {
            return 0;
        }
        int res = 0, cur = 0;
        for (int i = 30; ~i; i --) {
            bool j = val >> i & 1;
            if (!tr[cur].adj[!j]) {
                cur = tr[cur].adj[j];
            } else {
                res |= 1 << i;
                cur = tr[cur].adj[!j];
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

    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 1; i < n; i ++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    Trie tr;
    
    vector<int> sum(n + 1);
    auto dfs = [&](auto &self, int u, int p) -> void {
        tr.insert(sum[u]);
        for (auto &[v, w]: adj[u]) {
            if (v == p) {
                continue;
            }
            sum[v] = sum[u] ^ w;
            self(self, v, u);
        }
    };
    dfs(dfs, 1, 0);

    int ans = 0;
    for (int i = 1; i <= n; i ++) {
        cmax(ans, tr.query(sum[i]));
    }

    cout << ans << '\n';

    return 0;
}