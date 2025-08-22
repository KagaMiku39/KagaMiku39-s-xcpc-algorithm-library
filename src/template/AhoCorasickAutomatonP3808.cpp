#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

struct AhoCorasickAutomaton {
    int idx{};

    struct Node {
        int cnt, nx;
        array<int, 26> adj;
    };
    vector<Node> ac;

    AhoCorasickAutomaton() {
        ac.emplace_back();
    }

    void insert(string s) {
        int cur = 0;
        for (auto &ch : s) {
            int id = ch - 'a';
            if (!ac[cur].adj[id]) {
                ac[cur].adj[id] = ++ idx;
                ac.emplace_back();
            }
            cur = ac[cur].adj[id];
        }
        ac[cur].cnt ++;
    }

    void build() {
        queue<int> q;
        for (int i = 0; i < 26; i ++) {
            if (~ac[0].adj[i]) {
                if (int v = ac[0].adj[i]) {
                    q.push(v);
                }
            }
        }
        while (ssize(q)) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < 26; i ++) {
                int v = ac[u].adj[i];
                if (v) {
                    ac[v].nx = ac[ac[u].nx].adj[i];
                    q.push(v);
                } else {
                    ac[u].adj[i] = ac[ac[u].nx].adj[i];
                }
            }
        }
    }

    int query(string t) {
        int ans = 0, cur = 0;
        for (auto &ch : t) {
            int id = ch - 'a';
            cur = ac[cur].adj[id];
            for (int i = cur; i && ~ac[i].cnt; i = ac[i].nx) {
                ans += ac[i].cnt;
                ac[i].cnt = -1;
            }
        }
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    AhoCorasickAutomaton ac;
    for (int i = 1; i <= n; i ++) {
        string s;
        cin >> s;
        ac.insert(s);
    }
    
    ac.build();
    
    string t;
    cin >> t;

    cout << ac.query(t) << '\n';

    return 0;
}