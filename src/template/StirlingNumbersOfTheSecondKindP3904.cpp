#include <bits/stdc++.h>

#define ssize(x) int((x).size())

using namespace std;

struct BigInteger {
    string s{"0"};

    void getstr(string &str) const {
        size_t pos = str.find_first_not_of('0');
        if (pos == string::npos) {
            str = "0";
        } else {
            str = str.substr(pos);
        }
    }

    BigInteger operator + (const BigInteger &bi) const {
        vector<int> a(ssize(s)), b(ssize(bi.s));
        string res;
        int car = 0;
        for (int i = 0; i < ssize(s); i ++) {
            a[i] = s[ssize(s) - 1 - i] - '0';
        }
        for (int i = 0; i < ssize(bi.s); i ++) {
            b[i] = bi.s[ssize(bi.s) - 1 - i] - '0';
        }
        for (int i = 0; i < max(ssize(a), ssize(b)); i ++) {
            if (i < ssize(a)) {
                car += a[i];
            }
            if (i < ssize(b)) {
                car += b[i];
            }
            res += car % 10 + '0';
            car /= 10;
        }
        if (car) {
            res += '1';
        }
        reverse(begin(res), end(res));
        getstr(res);
        return BigInteger{res};
    }

    BigInteger operator * (const int &x) const {
        vector<int> a(ssize(s));
        int car = 0;
        string res;
        for (int i = 0; i < ssize(s); i ++) {
            a[i] = s[ssize(s) - 1 - i] - '0';
        }
        for (int i = 0; i < ssize(a); i ++) {
            car += a[i] * x;
            res += car % 10 + '0';
            car /= 10;
        }
        while (car) {
            res += car % 10 + '0';
            car /= 10;
        }
        reverse(begin(res), end(res));
        getstr(res);
        return BigInteger{res};
    }
};

istream &operator >> (istream &is, BigInteger &bi) {
    return is >> bi.s;
}

ostream &operator << (ostream &os, const BigInteger &bi) {
    for (auto &ch : bi.s) {
        os << ch;
    }
    return os;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    if (m > n) {
        cout << "0\n";
        return 0;
    }

    vector<vector<BigInteger>> dp(n + 1, vector<BigInteger>(m + 1));

    dp[0][0] = BigInteger{"1"};
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= m; j ++) {
            dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j] * j;
        }
    }

    cout << dp[n][m] << '\n';

    return 0;
}