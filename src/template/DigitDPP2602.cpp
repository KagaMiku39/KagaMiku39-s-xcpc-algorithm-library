#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long; 
using i128 = __int128; 

template<typename T>
bool cmin(T &a, const T &b) {
    return a > b ? a = b, true : false;
}

template<typename T>
bool cmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    i64 a, b;
    cin >> a >> b;

    vector<i64> dp(13), ba(13);
    ba[0] = 1; 
    for (int i = 1; i <= 12; i ++) {
        ba[i] = 10 * ba[i - 1];
        dp[i] = 10 * dp[i - 1] + ba[i - 1];
    }

    auto getdp = [&](i64 x) {
        i64 tmp = x;
        vector<int> vec{{}};
        while (tmp) {
            vec.emplace_back(tmp % 10);
            tmp /= 10;
        }
        vector<i64> res(10);
        for (int i = ssize(vec) - 1; i; i --) {
            for (int j = 0; j < vec[i]; j ++) {
                res[j] += ba[i - 1];
            }
            for (int j = 0; j <= 9; j ++) {
                res[j] += dp[i - 1] * vec[i];
            }
            res[0] -= ba[i - 1];
            x -= vec[i] * ba[i - 1];
            res[vec[i]] += x + 1;
        }
        return res;
    };

    auto lo = getdp(a - 1), ro = getdp(b);
    for (int i = 0; i < 10; i ++) {
        cout << ro[i] - lo[i] << " \n"[i == 9];
    } 

    return 0;
}