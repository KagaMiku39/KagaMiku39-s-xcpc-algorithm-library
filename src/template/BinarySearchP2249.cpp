#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }

    while (m --) {
        int num;
        cin >> num;
        int lo = 0, ro = n;
        auto pred = [&](int x) -> bool {
            return a[x] >= num;
        };
        while (lo + 1 < ro) {
            int mid = lo + (ro - lo) / 2;
            if (pred(mid)) {
                ro = mid;
            } else {
                lo = mid;
            }
        }
        cout << (a[ro] == num ? ro : -1) << " \n"[!m];
    }

    return 0;
}