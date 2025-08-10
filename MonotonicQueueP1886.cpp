#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }

    deque<int> dq[2];
    vector<vector<int>> ans(2, vector<int>(n + 1));
    for (int i = 1; i <= n; i ++) {
        for (int j = 0; j < 2; j ++) {
            if (ssize(dq[j]) && dq[j].front() + k - 1 < i) {
                dq[j].pop_front();
            }
            int l = j ? -1 : 1;
            while (ssize(dq[j]) && a[dq[j].back()] * l >= a[i] * l) {
                dq[j].pop_back();
            }
            dq[j].emplace_back(i);
            ans[j][i] = a[dq[j].front()];
        }
    }

    for (int i = 0; i < 2; i ++) {
        for (int j = k; j <= n; j ++) {
            cout << ans[i][j] << " \n"[j == n];
        }
    }

    return 0;
}