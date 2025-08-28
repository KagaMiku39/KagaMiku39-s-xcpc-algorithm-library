#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }
    
    sort(a.begin() + 1, a.end());

    vector<int> b(n + 1);
    for (int i = n; i >= 1; i --) {
        b[n - i + 1] = a[i] - a[i - 1] - 1;
    }

    int sum = 0;
    for (int i = 1; i <= n; i += 2) {
        sum ^= b[i];
    }

    cout << (sum ? "Georgia will win\n" : "Bob will win\n");    
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;

    while (t --) {
        solve();
    }

    return 0;
}