#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n;
    cin >> n;
    if (n & 1) {
        if (n < 27) {
            cout << "-1\n"; 
            return; 
        }
        n -= 27;
        cout << "1 3 3 4 4 5 5 6 6 1 2 7 7 8 8 9 9 10 10 11 11 12 12 13 13 1 2 ";
        for (int i = 14; i - 13 <= n / 2; i ++) {
            cout << i << ' ' << i << " \n"[i - 13 == n / 2];
        }
        return; 
    }
    for (int i = 1; i <= n / 2; i ++) {
        cout << i << ' ' << i << " \n"[i == n / 2];
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