#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

using u64 = unsigned long long; 

constexpr int maxa = 5e6 + 1;

bitset<maxa> isprime;

vector<int> prime;

mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

u64 h[maxa];

void solve() {   
    int n;
    cin >> n;
    
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }

    if (n & 1) {
        cout << "Yes\n";
        return;
    }

    if (n == 2) {
        cout << (a[1] == a[2] ? "Yes\n" : "No\n");
        return;
    }

    u64 sum = 0;
    for (int i = 1; i <= n; i ++) {
        sum ^= h[a[i]];
    }
    
    cout << (sum ? "No\n" : "Yes\n");
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    isprime.set();
    isprime[0] = isprime[1] = false;
    for (int i = 2; i < maxa; i ++) {
        if (isprime[i]) {
            prime.emplace_back(i);
            h[i] = rnd();
        }
        for (int &j: prime) {
            if (1ll * i * j >= maxa) {
                break;
            }
            h[i * j] = h[i] ^ h[j];
            isprime[i * j] = false;
            if (i % j == 0) {
                break;
            }
        }
    }

    int t;
    cin >> t;

    while (t --) {
        solve();
    }

    return 0;
}