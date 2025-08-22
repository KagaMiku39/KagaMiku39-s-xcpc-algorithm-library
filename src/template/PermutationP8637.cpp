#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> adj(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> adj[i];
    }

    int ans = n;
    vector<int> vis(n + 1);
    for (int i = 1; i <= n; i ++) {
        if (vis[i]) {
            continue;
        }
        for (int cur = i; !vis[cur]; cur = adj[cur]) {
            vis[cur] = true;
        }
        ans --;
    }

    cout << ans << '\n';
    
    return 0;
}