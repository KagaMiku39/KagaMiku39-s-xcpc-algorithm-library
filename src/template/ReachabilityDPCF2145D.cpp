#include <bits/stdc++.h>

using namespace std;

constexpr int maxn = 31;

bool dp[maxn][maxn * maxn];

void solve() {   
    int n, k;
    cin >> n >> k;

    if (!dp[n][n * (n - 1) / 2 - k]) {
        cout << "0\n";
        return;
    }
    
    int a = n, b = n * (n - 1) / 2 - k;
    vector<int> vec;
    while (1) {
        if (!a) {
            break;
        }
        for (int i = 1; i <= a && i * (i - 1) / 2 <= b; i ++) {
            if (dp[a - i][b - i * (i - 1) / 2]) {
                vec.emplace_back(i);
                a -= i;
                b -= i * (i - 1) / 2;
                break;
            }
        }
    }
 
    sort(begin(vec), end(vec));

    int tmp = n;
    vector<int> ans;
    for (int &i: vec) {
        for (int j = tmp - i + 1; j <= tmp; j ++) {
            ans.emplace_back(j);
        }
        tmp -= i;
    }

    for (int &i: ans) {
        cout << i << " \n"[i == ans.back()];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    dp[0][0] = true;
    for (int i = 0; i < maxn; i ++) {
        for (int j = 0; j < maxn * maxn; j ++) {
            for (int k = 1; i + k < maxn && j + k * (k - 1) / 2 <= maxn * maxn; k ++) {
                dp[i + k][j + k * (k - 1) / 2] |= dp[i][j];
            }
        }
    }

    while (t --) {
        solve();
    }

    return 0;
}