#include <bits/stdc++.h>

using namespace std;

constexpr int maxn = 1e8 + 1;

bitset<maxn> ispri;

vector<int> pri;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, q; 
    cin >> n >> q;
    
    ispri.set();
    ispri[0] = ispri[1] = false;
    for (int i = 2; i < maxn; i ++) {
        if (ispri[i]) {
            pri.emplace_back(i);
        }
        for (int &j: pri) {
            if (1ll * i * j > maxn) {
                break;
            }
            ispri[i * j] = false;
            if (i % j == 0) {
                break;
            }
        }
    }

    while (q --) {
        int k;
        cin >> k;
        cout << pri[k - 1] << '\n';
    }

    return 0;
}