#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n; 
    cin >> n;
    
    int off[4][2]{0, 1, 1, 0, 0, -1, -1, 0};
    
    int r = (n + 1) / 2, c = (n + 1) / 2;
    bool tag = false; 
    vector<vector<int>> mat(n + 1, vector<int>(n + 1));
    for (int ste = 1, idx = 1, dir = 0; idx < n * n; ste ++) {
        for (int i = 0; i < 2 && !tag; i ++, dir = (dir + 1) % 4) {
            for (int j = 1; j <= ste; j ++) {
                int nr = r + off[dir][0], nc = c + off[dir][1];
                if (nr < 1 || nc < 1 || nr > n || nc > n) {
                    tag = true;
                    break;
                }
                r = nr;
                c = nc;
                mat[r][c] = idx ++;
            }
        }
    }
    
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) {
            cout << mat[i][j] << " \n"[j == n];
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