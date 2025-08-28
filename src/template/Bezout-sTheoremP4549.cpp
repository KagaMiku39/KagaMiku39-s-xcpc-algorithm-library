#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }

    int g = 0;
    for (int i = 1; i <= n; i ++) {
        g = gcd(g, a[i]);
    }

    cout << g << '\n';
    
    return 0;
}