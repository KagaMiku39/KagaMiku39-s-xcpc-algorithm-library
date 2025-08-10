#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

template<typename T>
bool cmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

struct SuffixAutomaton {
    int last, idx{};

    struct Node {
        int len, nx, cnt;

        array<int, 26> adj;
    };
    vector<Node> sam;
    
    vector<vector<int>> adj;

    SuffixAutomaton() {
        sam.emplace_back();
        sam[0].nx = -1;
        adj.emplace_back();
    }

    void extend(char ch) {
        int id = ch - 'a';
        int p = last, cur = ++ idx;
        sam.emplace_back();
        adj.emplace_back();
        sam[cur].len = sam[p].len + 1;
        sam[cur].cnt ++;
        for (; ~p && !sam[p].adj[id]; p = sam[p].nx) {
            sam[p].adj[id] = cur;
        }
        if (~p) {
            sam[cur].nx = 0;
            last = cur;
            return;
        }
        int q = sam[p].adj[id];
        if (sam[q].len == sam[p].len + 1) {
            sam[cur].nx = q;
        } else {
            int qq = ++ idx;
            sam.emplace_back();
            adj.emplace_back();
            sam[qq].len = sam[p].len + 1;
            sam[qq].nx = sam[q].nx;
            sam[qq].adj = sam[q].adj;
            sam[cur].nx = sam[q].nx = qq;
            for (; ~p && sam[p].adj[id] == q; p = sam[p].nx) {
                sam[p].adj[id] = qq;
            }
        }
        last = cur;
    }

    i64 getans() {
        for (int i = 1; i <= idx; i ++) {
            adj[sam[i].nx].emplace_back(i);
        }
        i64 res = 0;
        auto dfs = [&](auto &dfs, int u) -> void {
            for (auto &v: adj[u]) {
                dfs(dfs, v);
                sam[u].cnt += sam[v].cnt;
            }
            if (sam[u].cnt > 1) {
                cmax(res, 1ll * sam[u].cnt * sam[u].len);
            }
        };
        dfs(dfs, 0);
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    SuffixAutomaton sam;
    for (auto &ch: s) {
        sam.extend(ch);
    }

    cout << sam.getans() << '\n';

    return 0;
}