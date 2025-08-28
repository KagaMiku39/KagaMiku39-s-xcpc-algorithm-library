#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n;
    cin >> n;
    
    vector<int> vec(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> vec[i];
    }

    int ans = 0;
    for (int i = 1; i <= n; i ++) {
        ans ^= vec[i];
    }
    
    cout << (ans ? "Yes\n" : "No\n");
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