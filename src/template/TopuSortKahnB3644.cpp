#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
	int n;
    cin >> n;

    vector<int> in(n + 1); 
    vector<vector<int>> adj(n + 1); 
	for (int i = 1; i <= n; i ++) {
        int a;
		while (cin >> a) {
            if (!a) break;
			in[a] ++;
			adj[i].push_back(a);
		}
	}

    int idx = 0;
    
    queue<int> q;
	for (int i = 1; i <= n; i ++) {
		if (!in[i]) {
			q.push(i);
			cout << i << " \n"[++ idx == n];	
		}
    }
    
	while (!q.empty()) {
		int u = q.front();
        q.pop();
		for (auto &v: adj[u]) {
			in[v] --;
			if (!in[v]) {
				q.push(v);
                cout << v << " \n"[++ idx == n];	
			}
		}
	}

    return 0;
}