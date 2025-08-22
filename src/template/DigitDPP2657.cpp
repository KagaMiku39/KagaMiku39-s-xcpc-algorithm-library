#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int arr[12]{}, dp[12][10]{};

    for (int i = 0; i <= 9; i ++) {
        dp[1][i] = 1;
    }
    for (int i = 2; i < 12; i ++) {
        for (int j = 0; j <= 9; j ++) {
            for (int k = 0; k <= 9; k ++) {
                if (abs(k - j) >= 2) {
                    dp[i][j] += dp[i - 1][k];
                }
            }
        }
    }

    auto getdp = [&](int x) -> int {
        if (!x) {
            return 0;
        }
        int cnt = 0, tmp = x;
        while (tmp) {
            arr[++ cnt] = tmp % 10;
            tmp /= 10;
        }
        int res = 0, last = -2;
        for (int i = cnt; i; -- i) {
            int now = arr[i];
            for (int j = (i == cnt); j < now; ++ j) {
                if (abs(j - last) >= 2) {
                    res += dp[i][j];
                }
            }
            if (abs(now - last) < 2) {
                break;
            }
            last = now;
            if (i == 1) {
                res ++;
            }
        }
        for (int i = 1; i < cnt; i ++) {
            for (int j = 1; j <= 9; j ++) {
                res += dp[i][j];
            }
        }
        return res;
    };
    
    int l, r;
    cin >> l >> r;
    
    cout << getdp(r) - getdp(l - 1) << '\n';
    
    return 0;
}