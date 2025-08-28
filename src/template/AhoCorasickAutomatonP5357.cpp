#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

struct AhoCorasickAutomaton {
    int idx{};
    
    vector<int> topo;

    struct Node {
        int nx;

        array<int, 26> adj;
        
        vector<int> id;
    };
    vector<Node> ac;

    AhoCorasickAutomaton() {
        ac.emplace_back();
    }
    
    void insert(string& s, int ind) {
        int cur = 0;
        for (char &ch: s) {
            int id = ch - 'a';
            if (!ac[cur].adj[id]) {
                ac[cur].adj[id] = ++ idx;
                ac.emplace_back();
            }
            cur = ac[cur].adj[id];
        }
        ac[cur].id.push_back(ind);
    }

    void build() {
        queue<int> q;
        for (int i = 0; i < 26; i ++) {
            if (int v = ac[0].adj[i]) {
                q.push(v);
            }
        }
        while (ssize(q)) {
            int u = q.front();
            q.pop();
            topo.push_back(u);
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

    void solve(int n, string& t) {
        int cur = 0;
        vector<int> cnt(ssize(ac));
        for (char &ch: t) {
            int id = ch - 'a';
            cur = ac[cur].adj[id];
            cnt[cur] ++;
        }
        for (int i = idx - 1; i; i --) {
            int j = topo[i];
            cnt[ac[j].nx] += cnt[j];
        }
        vector<int> ans(n + 1);
        for (int i = 1; i <= idx; i ++) {
            for (int p: ac[i].id) {
                ans[p] = cnt[i];
            }
        }
        for (int i = 1; i <= n; i ++) {
            cout << ans[i] << '\n';
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    AhoCorasickAutomaton ac;
    
    vector<string> s(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> s[i];
        ac.insert(s[i], i);
    }
    
    ac.build();
    
    string t;
    cin >> t;
    
    ac.solve(n, t);

    return 0;
}