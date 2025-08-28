#include <bits/stdc++.h>

using namespace std;

struct Trie {
    int idx{}; 
    
    struct Node{
        int id, cnt;
        
        array<int, 62> adj;
    };
    vector<Node> tr; 
    
    Trie() {
        tr.emplace_back(); 
    }
    
    int getid(char ch) {
        if (isdigit(ch)) {
            return ch - '0';
        }
        if (ch >= 'A' && ch <= 'Z') {
            return 10 + ch - 'A';
        } else {
            return 36 + ch - 'a';
        }
    }
    
    void insert(string s) {
        int cur = 0;
        for (char &ch: s) {
            int id = getid(ch);
            if (!tr[cur].adj[id]) {
                tr[cur].adj[id] = ++ idx;
                tr.emplace_back();
            }
            cur = tr[cur].adj[id];
            tr[cur].cnt ++;
        }
    }

    int query(string s) {
        int cur = 0;
        for (char &ch: s) {
            int id = getid(ch);
            if (!tr[cur].adj[id]) {
                return 0;
            }
            cur = tr[cur].adj[id];
        }
        return tr[cur].cnt;
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    
    Trie tr;

    for (int i = 1; i <= n; i ++) {
        string s;
        cin >> s;
        tr.insert(s);
    }
    
    while (q --) {
        string s;
        cin >> s;
        cout << tr.query(s) << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; 
    cin >> t; 
    
    while (t --) {
        solve();
    }

    return 0;
}