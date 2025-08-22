#include <bits/stdc++.h>

using namespace std;

constexpr int maxn = 1e6 + 1;

bitset<maxn> isprime;

vector<int> prime, ans;

int lam[maxn];

void solve() {
    int n;
    cin >> n;

    for (int i = 0; i < n / 2; i ++) {
        cout << ans[i] << " \n"[i == n / 2 - 1];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    isprime.set();
    isprime[0] = isprime[1] = false;
    lam[1] = 1;
    for (int i = 2; i < maxn; i ++) {
        if (isprime[i]) {
            prime.emplace_back(i);
            lam[i] = -1;
        }
        for (int &j: prime) {
            if (1ll * i * j >= maxn) {
                break;
            }
            isprime[i * j] = false;
            lam[i * j] = -lam[i];
            if (i % j == 0) {
                break;
            }
        }
    }

    for (int i = 2; i < maxn; i ++) {
        if (!~lam[i]) {
            ans.emplace_back(i);
        }
    }
    
    int t;
    cin >> t;

    while (t --) {
        solve();
    }

    return 0;
}