#include <bits/stdc++.h>

using namespace std;

void solve() {   
    int n;
    cin >> n;

    vector<int> f(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> f[i];
    }

    // vector<vector<int>> ans(n + 1, vector<int>(n + 1));
    // ans[1][1] = 0;
    // for (int i = 2; i <= n; i ++) {
    //     if (f[i] == 1) {
    //         continue;
    //     }
    //     ans[i][i] = 1;
    //     for (int j = 1; j <= i; j ++) {
    //         if (j < f[i] - 1) {
    //             ans[i][j] = j + 1;
    //             ans[j][i] = j + 1;
    //         }
    //     }
    // }

    vector<int> id(n + 1);

    iota(begin(id), end(id), 0);

    sort(next(begin(id)), end(id), [&](const int &l, const int &r) {
        return f[l] < f[r];
    });
    
    vector<int> vec(n + 1, -1); 
    for (int i = 1, j = 0, k = 0; i <= n; i ++) {
        j = id[i];
        if (f[j] != f[k]) {
            vec[i] = f[k];
        }
        k = j;
    }
    
    vector<int> vis(n + 1);
    for (int i = 1; i <= n; i ++) {
        vis[f[i]] = true;
    }
        
    int idx = 1;
    for (int i = 1; i <= n; i ++) {
        if (~vec[i]) {
            continue;
        }
        while (vis[idx]) {
            idx ++;
        }
        vec[i] = idx;
        vis[idx] = true;
    }

    vector<vector<int>> ans(n + 1, vector<int>(n + 1));
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) {
            ans[id[i]][id[j]] = vec[min(i, j)];
        }
    }

    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) {
            cout << ans[i][j] << " \n"[j == n];
        }
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