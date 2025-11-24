#include <bits/stdc++.h>

using namespace std;

void solve() {   
    int n;
    cin >> n;

    vector<string> mat(2);
    for (int i = 0; i < 2; i ++) {
        cin >> mat[i];
        mat[i] = ' ' + mat[i] + ' ';
    }

    int dp = 0;
    bool tag = false, ok = false;
    for (int i = 1; i <= n + 1; i ++) {
        if (mat[0][i] == '.' && mat[1][i] == '#') {
            if (dp == 0) {
                dp = 1;
            } else if (dp == 1) {
                dp = 0;
            } else {
                cout << "None\n";
                return;
            }
            tag = false;
        } else if (mat[0][i] == '#' && mat[1][i] == '.') {
            if (dp == 0) {
                dp = 2;
            } else if (dp == 2) {
                dp = 0;
            } else {
                cout << "None\n";
                return;
            }
            tag = false;
        } else if (mat[0][i] == '.' && mat[1][i] == '.') {
            if (dp == 1) {
                dp = 2;
            } else if (dp == 2) {
                dp = 1;
            } else {
                if (tag) {
                    ok = true;
                }
                tag = true;
            }
        } else {
            if (dp) {
                cout << "None\n";
                return;
            }
            tag = false;
        }
    }

    cout << (ok ? "Multiple\n" : "Unique\n");
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