#include <bits/stdc++.h>

using namespace std;

constexpr int maxn = 1e8 + 1;

bitset<maxn> isprime;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, q; 
    cin >> n >> q;
    
    vector<int> prime;
    isprime.set();
    isprime[0] = isprime[1] = false;
    for (int i = 2; i < maxn; i ++) {
        if (isprime[i]) {
            prime.emplace_back(i);
        }
        for (int &j: prime) {
            if (1ll * i * j > maxn) {
                break;
            }
            isprime[i * j] = false;
            if (i % j == 0) {
                break;
            }
        }
    }

    while (q --) {
        int k;
        cin >> k;
        cout << prime[k - 1] << '\n';
    }

    return 0;
}