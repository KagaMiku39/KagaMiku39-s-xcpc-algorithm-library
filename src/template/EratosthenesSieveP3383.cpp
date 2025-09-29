#include <bits/stdc++.h>

using namespace std;

constexpr int maxn = 1e8 + 1;

bitset<maxn> isprime;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    isprime.set();
    isprime[0] = isprime[1] = false;
    for (int i = 2; i * i < maxn; i ++) {
        if (!isprime[i]) {
            continue;
        }
        for (int j = i * i; j < maxn; j += i) {
            isprime[j] = false;
        }
    }
    
    vector<int> prime{{}};
    for (int i = 2; i < maxn; i ++) {
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