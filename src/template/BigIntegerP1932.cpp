#include <bits/stdc++.h>

#define ssize(x) int((x).size())

using namespace std;

struct BigInteger {
    inline static double PI = acos(-1);

    string s{"0"};

    struct Complex {
        double x, y;
        Complex operator + (const Complex &t) const {
            return {x + t.x, y + t.y};
        }
        Complex operator - (const Complex &t) const {
            return {x - t.x, y - t.y};
        }
        Complex operator * (const Complex &t) const {
            return {x * t.x - y * t.y, x * t.y + y * t.x};
        }
    };

    static void fft(vector<Complex> &vec, int n, int op) {
        vector<int> r(n);
        for (int i = 0; i < n; i ++) {
            r[i] = (r[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
        }
        for (int i = 0; i < n; i ++) {
            if (i < r[i]) {
                swap(vec[i], vec[r[i]]);
            }
        }
        for (int i = 2; i <= n; i <<= 1) {
            Complex w1({cos(2 * PI / i), sin(2 * PI / i) * op});
            for (int j = 0; j < n; j += i) {
                Complex wk({1, 0});
                for (int k = j; k < j + i / 2; k ++) {
                    Complex x = vec[k], y = vec[k + i / 2] * wk;
                    vec[k] = x + y;
                    vec[k + i / 2] = x - y;
                    wk = wk * w1;
                }
            }
        }
    }

    void getvec(vector<int> &vec) const {
        while (ssize(vec) > 1 && vec.back() == 0) {
            vec.pop_back();
        }
    }

    void getstr(string &str) const {
        size_t pos = str.find_first_not_of('0');
        if (pos == string::npos) {
            str = "0";
        } else {
            str = str.substr(pos);
        }
    }

    bool cmp(vector<int> &a, vector<int> &b) const {
        if (ssize(a) != ssize(b)) {
            return ssize(a) < ssize(b);
        }
        for (int i = ssize(a) - 1; ~i; i --) {
            if (a[i] != b[i]) {
                return a[i] < b[i];
            }
        }
        return false;
    }

    BigInteger operator + (const BigInteger &bi) const {
        if (s[0] == '-' && bi.s[0] == '-') {
            return BigInteger{'-' + (BigInteger{s.substr(1)} + BigInteger{bi.s.substr(1)}).s};
        }
        if (s[0] == '-') {
            return bi - BigInteger{s.substr(1)};
        }
        if (bi.s[0] == '-') {
            return *this - BigInteger{bi.s.substr(1)};
        }
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

    BigInteger& operator += (const BigInteger &bi) {
        return *this = *this + bi;
    }

    BigInteger operator - (const BigInteger &bi) const {
        if (s[0] == '-' && bi.s[0] == '-') {
            return BigInteger{bi.s.substr(1)} - BigInteger{s.substr(1)};
        }
        if (s[0] == '-') {
            return BigInteger{'-' + (BigInteger{s.substr(1)} + bi).s};
        }
        if (bi.s[0] == '-') {
            return *this + BigInteger{bi.s.substr(1)};
        }
        vector<int> a(ssize(s)), b(ssize(bi.s));
        string res;
        bool neg = false;
        for (int i = 0; i < ssize(s); i ++) {
            a[i] = s[ssize(s) - 1 - i] - '0';
        }
        for (int i = 0; i < ssize(bi.s); i ++) {
            b[i] = bi.s[ssize(bi.s) - 1 - i] - '0';
        }
        if (cmp(a, b)) {
            swap(a, b);
            neg = true;
        }
        for (int i = 0; i < ssize(a); i ++) {
            int j = a[i];
            if (i < ssize(b)) j -= b[i];
            if (j < 0) {
                j += 10;
                a[i + 1] --;
            }
            res += j + '0';
        }
        reverse(begin(res), end(res));
        getstr(res);
        if (neg && res != "0") {
            res = '-' + res;
        }
        return BigInteger{res};
    }

    BigInteger& operator -= (const BigInteger &bi) {
        return *this = *this - bi;
    }

    BigInteger operator * (const BigInteger &bi) const {
        if (s == "0" || bi.s == "0") {
            return BigInteger{"0"};
        }
        if (s[0] == '-' && bi.s[0] == '-') {
            return BigInteger{s.substr(1)} * BigInteger{bi.s.substr(1)};
        }
        if (s[0] == '-') {
            return BigInteger{'-' + (BigInteger{s.substr(1)} * bi).s};
        }
        if (bi.s[0] == '-') {
            return BigInteger{'-' + (*this * BigInteger{bi.s.substr(1)}).s};
        }
        int n = ssize(s), m = ssize(bi.s), len = 1;
        while (len < n + m) {
            len <<= 1;
        }
        vector<Complex> a(len), b(len);
        for (int i = 0; i < n; i ++) {
            a[i].x = s[n - 1 - i] - '0';
        }
        for (int i = 0; i < m; i ++) {
            b[i].x = bi.s[m - 1 - i] - '0';
        }
        fft(a, len, 1);
        fft(b, len, 1);
        for (int i = 0; i < len; i ++) {
            a[i] = a[i] * b[i];
        }
        fft(a, len, -1);
        vector<int> c(len);
        long long car = 0;
        for (int i = 0; i < len; i++) {
            long long val = (long long)(a[i].x / len + 0.5) + car;
            c[i] = val % 10;
            car = val / 10;
        }
        getvec(c);
        string res;
        for (auto &i : c) {
            res += i + '0';
        }
        reverse(begin(res), end(res));
        getstr(res);
        return BigInteger{res};
        // vector<int> a(ssize(s)), b(ssize(bi.s)), c(ssize(s) + ssize(bi.s));
        // string res;
        // for (int i = 0; i < ssize(s); i ++) {
        //     a[i] = s[ssize(s) - 1 - i] - '0';
        // }
        // for (int i = 0; i < ssize(bi.s); i ++) {
        //     b[i] = bi.s[ssize(bi.s) - 1 - i] - '0';
        // }
        // for (int i = 0; i < ssize(a); i ++) {
        //     for (int j = 0; j < ssize(b); j ++) {
        //         c[i + j] += a[i] * b[j];
        //         c[i + j + 1] += c[i + j] / 10;
        //         c[i + j] %= 10;
        //     }
        // }
        // getvec(c);
        // for (auto &i : c) {
        //     res += i + '0';
        // }
        // reverse(begin(res), end(res));
        // getstr(res);
        // return BigInteger{res};
    }

    BigInteger operator * (const int &x) const {
        vector<int> a(ssize(s)), b;
        int car = 0;
        string res;
        for (int i = 0; i < ssize(s); i ++) {
            a[i] = s[ssize(s) - 1 - i] - '0';
        }
        b.resize(ssize(s));
        for (int i = 0; i < ssize(a); i ++) {
            b[i] = a[i] * x + car;
            car = b[i] / 10;
            b[i] %= 10;
        }
        while (car) {
            b.push_back(car % 10);
            car /= 10;
        }
        getvec(b);
        for (auto &i : b) {
            res += i + '0';
        }
        reverse(begin(res), end(res));
        getstr(res);
        return BigInteger{res};
    }

    BigInteger& operator *= (const BigInteger &bi) {
        return *this = *this * bi;
    }

    BigInteger& operator *= (const int &num) {
        return *this = *this * num;
    }

    BigInteger operator / (const BigInteger &bi) const {
        if (s[0] == '-' && bi.s[0] == '-') {
            return BigInteger{s.substr(1)} / BigInteger{bi.s.substr(1)};
        }
        if (s[0] == '-') {
            return BigInteger{'-' + (BigInteger{s.substr(1)} / bi).s};
        }
        if (bi.s[0] == '-') {
            return BigInteger{'-' + (*this / BigInteger{bi.s.substr(1)}).s};
        }
        vector<int> a(ssize(s)), b(ssize(bi.s)), c;
        string res;
        for (int i = 0; i < ssize(s); i ++) {
            a[i] = s[ssize(s) - 1 - i] - '0';
        }
        for (int i = 0; i < ssize(bi.s); i ++) {
            b[i] = bi.s[ssize(bi.s) - 1 - i] - '0';
        }
        if (cmp(a, b)) {
            return BigInteger{"0"};
        }
        reverse(begin(a), end(a));
        for (int i = 0; i < ssize(a); i ++) {
            int j = 0;
            c.push_back(a[i]);
            reverse(begin(c), end(c));
            while (!cmp(c, b)) {
                for (int k = 0; k < ssize(c); k ++) {
                    if (k < ssize(b)) {
                        c[k] -= b[k];
                    }
                    if (c[k] < 0) {
                        c[k] += 10;
                        c[k + 1] --;
                    }
                }
                getvec(c);
                j ++;
            }
            reverse(begin(c), end(c));
            res += j + '0';
        }
        getstr(res);
        return BigInteger{res};
    }

    BigInteger operator / (const int &x) const {
        string res;
        int r = 0;
        for (auto &ch : s) {
            r = r * 10 + ch - '0';
            res += r / x + '0';
            r %= x;
        }
        getstr(res);
        return BigInteger{res};
    }

    BigInteger& operator /= (const BigInteger &bi) {
        return *this = *this / bi;
    }

    BigInteger& operator /= (const int &x) {
        return *this = *this / x;
    }

    BigInteger operator % (const BigInteger &bi) const {
        return *this - (*this / bi) * bi;
    }

    BigInteger& operator %= (const BigInteger &bi) {
        return *this = *this % bi;
    }

    bool operator < (const BigInteger &bi) const {
        if (s[0] != '-' && bi.s[0] == '-') {
            return false;
        }
        if (s[0] == '-' && bi.s[0] != '-') {
            return true;
        }
        if (s[0] == '-') {
            return BigInteger{s.substr(1)} > BigInteger{bi.s.substr(1)};
        }
        if (ssize(s) != ssize(bi.s)) {
            return ssize(s) < ssize(bi.s);
        }
        return s < bi.s;
    }

    bool operator > (const BigInteger &bi) const {
        if (s[0] != '-' && bi.s[0] == '-') {
            return true;
        }
        if (s[0] == '-' && bi.s[0] != '-') {
            return false;
        }
        if (s[0] == '-') {
            return BigInteger{s.substr(1)} < BigInteger{bi.s.substr(1)};
        }
        if (ssize(s) != ssize(bi.s)) {
            return ssize(s) > ssize(bi.s);
        }
        return s > bi.s;
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

    BigInteger a, b;
    cin >> a >> b;

    cout << a + b << '\n';
    cout << a - b << '\n';
    cout << a * b << '\n';
    cout << a / b << '\n';
    cout << a % b << '\n';

    return 0;
}