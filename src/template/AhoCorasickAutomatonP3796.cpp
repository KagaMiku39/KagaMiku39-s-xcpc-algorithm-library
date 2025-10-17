#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

template<typename T>
bool cmax(T &a, T &b) {
	return a < b ? a = b, true : false;
}

struct AhoCorasickAutomaton {
    int idx{};

    struct Node {
        int nx;

        vector<int> id;

        array<int, 26> adj;
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

    void solve(int n, string& t, vector<string>& s) {
        vector<int> cnt(n + 1);
        int cur = 0;
        for (char &ch: t) {
            int id = ch - 'a';
            cur = ac[cur].adj[id];
            for (int j = cur; j; j = ac[j].nx) {
                for (int i : ac[j].id) {
                    cnt[i] ++;
                }
            }
        }
        int mx = 0;
        for (int i = 1; i <= n; i ++) {
            cmax(mx, cnt[i]);
        }
        cout << mx << '\n';
        for (int i = 1; i <= n; i ++) {
            if (cnt[i] == mx) {
                cout << s[i] << '\n';
            }
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n && n) {
        AhoCorasickAutomaton ac;
        vector<string> s(n + 1);
        for (int i = 1; i <= n; i ++) {
            cin >> s[i];
            ac.insert(s[i], i);
        }
        ac.build();
        string t;
        cin >> t;
        ac.solve(n, t, s);
    }

    return 0;
}