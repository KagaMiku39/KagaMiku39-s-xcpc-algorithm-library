#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n, d;
    cin >> n >> d;
    
    cout << "1";
    if (d % 3 == 0 || n >= 3) {
        cout << " 3";
    }
    if (d == 5) {
        cout << " 5";
    }
    if (d == 7 || n >= 3) {
        cout << " 7";
    }
    if ((d % 3 == 0 && n >= 3) || n >= 6 || d == 9) {
        cout << " 9";
    }
    cout << '\n';    
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