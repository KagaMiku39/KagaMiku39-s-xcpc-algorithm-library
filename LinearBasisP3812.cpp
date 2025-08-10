#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

struct LinearBasis {
    vector<i64> vec;

    LinearBasis() : vec(64) {}

    bool insert(i64 x) {
        for (int i = 63; ~i; i --) {
            bool j = x >> i & 1;
            if (!j) {
                continue;
            }
            if (!vec[i]) {
                vec[i] = x; 
                return true;
            }
            x ^= vec[i];
        }
        return false;
    }

    i64 getsum() {
        i64 res = 0;
        for (int i = 63; ~i; i --) {
            if ((res ^ vec[i]) > res) {
                res ^= vec[i];
            }
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    LinearBasis lb;
    
    for (int i = 1; i <= n; i ++) {
        i64 x;
        cin >> x;
        lb.insert(x);
    }

    cout << lb.getsum() << '\n';

    return 0;
}