#include <bits/stdc++.h>

using namespace std;

const double PI = acos(-1);

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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    int len = 1;
    while (len <= n + m) {
        len *= 2;
    }

    vector<Complex> a(len), b(len);
    for (int i = 0; i <= n; i ++) {
        cin >> a[i].x;
    }
    for (int i = 0; i <= m; i ++) {
        cin >> b[i].x;
    }
    
    // vector<int> r(len);
    // auto fft = [&](vector<Complex> &vec, int n, int op) {
    //     for (int i = 0; i < n; i ++) {
    //         r[i] = (r[i / 2] / 2) | (i & 1 ? n / 2 : 0);
    //     }
    //     for (int i = 0; i < n; i ++) {
    //         if (i < r[i]) {
    //             swap(vec[i], vec[r[i]]);
    //         }
    //     }
    //     for (int i = 2; i <= n; i *= 2) {
    //         Complex w1{cos(2 * PI / i), sin(2 * PI / i) * op};
    //         for (int j = 0; j < n; j += i) {
    //             Complex wk{1, 0};
    //             for (int k = j; k < j + i / 2; k ++) {
    //                 Complex x = vec[k], y = vec[k + i / 2] * wk;
    //                 vec[k] = x + y;
    //                 vec[k + i / 2] = x - y;
    //                 wk = wk * w1;
    //             }
    //         }
    //     }
    // };

    auto fft = [&](auto &self, vector<Complex> &vec, int n, int op) -> void {
        if (n == 1) {
            return;
        }
        vector<Complex> a1(n / 2), a2(n / 2);
        for (int i = 0; i < n / 2; i ++) {
            a1[i] = vec[i * 2];
            a2[i] = vec[i * 2 + 1];
        }
        self(self, a1, n / 2, op);
        self(self, a2, n / 2, op);
        Complex w1{cos(2 * PI / n), sin(2 * PI / n) * op};
        Complex wk{1, 0};
        for (int i = 0; i < n / 2; i ++) {
            vec[i] = a1[i] + a2[i] * wk;
            vec[i + n / 2] = a1[i] - a2[i] * wk;
            wk = wk * w1;
        }
    };

    // fft(a, len, 1);
    // fft(b, len, 1);

    fft(fft, a, len, 1);
    fft(fft, b, len, 1);

    for (int i = 0; i < len; i ++) {
        a[i] = a[i] * b[i];
    }

    // fft(a, len, -1);

    fft(fft, a, len, -1);

    for (int i = 0; i <= n + m; i ++) {
        cout << (int)(a[i].x / len + 0.5) << " \n"[i == n + m];
    }

    return 0;
}