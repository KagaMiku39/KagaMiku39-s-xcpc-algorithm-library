#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<bool> isprime(n + 1, true);
    isprime[0] = isprime[1] = false;
    for (int i = 2; i * i <= n; i ++) {
        if (!isprime[i]) {
            continue;
        }
        for (int j = i * i; j <= n; j += i) {
            isprime[j] = false;
        }
    }
    
    vector<int> prime{{}};
    for (int i = 2; i <= n; i ++) {
        if (isprime[i]) {
            prime.emplace_back(i);
        }
    }

    while (q --) {
        int k;
        cin >> k;
        cout << prime[k] << '\n';
    }
    
    return 0;
}